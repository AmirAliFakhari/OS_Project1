// user/threadtest.c (نسخه صحیح و نهایی)

#include "kernel/types.h"
#include "user/user.h"

#define STACK_SIZE  4096 // یک اندازه مناسب برای پشته

void *my_thread(void *arg) {
  uint64 number = (uint64) arg;
  for (int i = 0; i < 100; ++i) {
    number++;
    printf("thread: %lu\n", number);
    sleep(1); // یک sleep کوتاه اضافه می‌کنیم تا اجرای نخ‌ها در هم تنیده شود
  }
  return (void *) number;
}

int main(int argc, char *argv[]) {
  // پشته‌ها را با malloc تخصیص بده تا از تراز بودن آنها مطمئن شوی
  void *sp1 = malloc(STACK_SIZE);
  void *sp2 = malloc(STACK_SIZE);
  void *sp3 = malloc(STACK_SIZE);
  
  // آدرس بالای پشته را به تابع پاس بده
  int ta = thread(my_thread, sp1 + STACK_SIZE, (void *) 100);
  printf("NEW THREAD CREATED %d\n", ta);
  
  int tb = thread(my_thread, sp2 + STACK_SIZE, (void *) 200);
  printf("NEW THREAD CREATED %d\n", tb);
  
  int tc = thread(my_thread, sp3 + STACK_SIZE, (void *) 300);
  printf("NEW THREAD CREATED %d\n", tc);

  jointhread(ta);
  jointhread(tb);
  jointhread(tc);
  
  // حافظه تخصیص داده شده را آزاد کن
  free(sp1);
  free(sp2);
  free(sp3);

  printf("DONE\n");
  
  exit(0);
}