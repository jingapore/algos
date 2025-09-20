extern "C" {
extern unsigned char __heap_base; // tiny bump allocator
static unsigned int bump = (unsigned int)&__heap_base;
void *alloc(int size) {
  unsigned int p = bump;
  bump += (size + 7) & ~7;
  return (void *)p;
}

// events are triples of int32: {code,i,j}
// code: 1=L1 compare, 2=L2 compare, 3=L3 swap, 4=L4 swap, 9=done
int next_perm_trace(int *data, int n, int *out, int out_cap_triples) {
  int count = 0;
  auto push = [&](int c, int i, int j) {
    if (count < out_cap_triples) {
      out[3 * count + 0] = c;
      out[3 * count + 1] = i;
      out[3 * count + 2] = j;
    }
    ++count;
  };
  if (n < 2) {
    push(9, 0, 0);
    return count;
  }
  // L1: find rightmost ascent
  int i = n - 2;
  for (; i >= 0; --i) {
    push(1, i, i + 1);
    if (data[i] < data[i + 1])
      break;
  }
  if (i < 0) { // reverse whole array (L4) and return false
    int l = 0, r = n - 1;
    while (l < r) {
      push(4, l, r);
      int t = data[l];
      data[l] = data[r];
      data[r] = t;
      ++l;
      --r;
    }
    push(9, 0, 0);
    return count;
  }
  // L2: rightmost successor
  int j = n - 1;
  for (; j > i; --j) {
    push(2, i, j);
    if (data[i] < data[j])
      break;
  }
  // L3: swap pivot & successor
  push(3, i, j);
  {
    int t = data[i];
    data[i] = data[j];
    data[j] = t;
  }
  // L4: reverse suffix
  int l = i + 1, r = n - 1;
  while (l < r) {
    push(4, l, r);
    int t = data[l];
    data[l] = data[r];
    data[r] = t;
    ++l;
    --r;
  }
  push(9, 0, 0);
  return count;
}
}
