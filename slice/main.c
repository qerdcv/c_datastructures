#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct
{
  int len;
  int cap;
  void *ptr;
} Slice;

Slice new_int_slice(int len, int cap)
{
  Slice s = {
    .len = len,
    .cap = cap,
    .ptr = calloc(cap, sizeof(int)),
  };
  return s;
}

int get_int(Slice s, int idx)
{
  assert(idx < s.len && "Index out of range");

  return *((int *)s.ptr + idx);
}

void put_int(Slice s, int idx, int val)
{
  assert(idx < s.len && "Index out of range");

  int *t_ptr = (int *)s.ptr + idx;
  *t_ptr = val;
}

int pop_int(Slice *s)
{
  assert(s->len > 0 && "Nothing to pop");
  s->len--;

  int *t_ptr = (int *)s->ptr + s->len;
  int result = *t_ptr;
  *t_ptr = 0;

  return result;
}

void append_int(Slice *s, int val)
{
  if (s->len == s->cap)
  {
    s->cap = (s->cap * 2) + 5;

    s->ptr = realloc(s->ptr, sizeof(int) * s->cap);

    for (int i = s->len; i < s->cap; ++i)
    {
      int *t_ptr = (int *)s->ptr + i;
      *t_ptr = 0;
    }
  }

  int *t_ptr = (int *)s->ptr + s->len;
  *t_ptr = val;
  s->len++;
}

void destroy_slice(Slice *s)
{
  free(s->ptr);
}


int main()
{
  Slice s = new_int_slice(0, 0);

  append_int(&s, 1);
  append_int(&s, 2);
  append_int(&s, 3);
  append_int(&s, 4);
  append_int(&s, 5);
  append_int(&s, 6);

  for (int i = 0; i < s.len; i++)
  {
    printf("%d\n", get_int(s, i));
  }

  return 0;
}
