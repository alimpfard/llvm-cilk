/**
 * Runtime System for Cilk
 *
 * Adds userspace N:M lightweight threads
 */
 #include <stdlib.h>
 #include "sewing/include/sewing.h"
 #include <malloc.h>

#define MAX_JOB_COUNT 4096

static size_t cilk_rts_job = 0;
static Sew_Stitch cilk_rts_jobs[MAX_JOB_COUNT];
static void* cilk_rts_results[MAX_JOB_COUNT] = {0};
static struct Sewing* cilk_rts_sewing = NULL;

struct cilk_lwt {
  void *(*start_routine)(void*);
  void *arg;
  size_t id;
};

void cilk_run_lwt(void* _lwt) {
  struct cilk_lwt *lwt = _lwt;
  cilk_rts_results[lwt->id] = lwt->start_routine(lwt->arg);
}
/**
 * Cilk Lightweight Thread Create
 *
 * Creates an lwt
 */
int cilk_lwt_create(__int64_t *thread, const int* attr, void *(*start_routine)(void*), void *arg) {
  if (cilk_rts_job>=MAX_JOB_COUNT)
    abort();
  Sew_Stitch *job = cilk_rts_jobs+cilk_rts_job;
  job->procedure = cilk_run_lwt;
  struct cilk_lwt *sarg = malloc(sizeof(struct cilk_lwt)); // TODO BUG: Fix leak here
  if (!sarg) {
    return 1;
  }
  sarg->start_routine = start_routine;
  sarg->arg = arg;
  sarg->id = cilk_rts_job;
  job->argument = sarg;
  job->name = "CilkFiberRoutine";
  *thread = cilk_rts_job++;
  return 0;
}

/**
 * Cilk Lightweight Thread Wait
 *
 * Yields the actual thread and sets *retval to the return value
 * of the provided lwt
 */
int cilk_lwt_wait(int thread, void **retval) {
  sew_stitches_and_wait(cilk_rts_sewing, cilk_rts_jobs+thread, 1); // wait for yee bit
  *retval = cilk_rts_results[thread];
  return 0;
}

void cilk_rts_run_main (struct Sewing* sewing, Sew_Thread* threads, size_t thread_count, Sew_Procedure_Argument arg) {
  void (*main)(void*) = arg;
  Sew_Stitch *mainj = cilk_rts_jobs+(cilk_rts_job++);
  mainj->procedure = main;
  mainj->argument = NULL;
  mainj->name = "CilkRTSMain";
  cilk_rts_sewing = sewing;
#ifdef DEBUG
  printf("Strapped main function %p\n", main);
  printf("Sewing now: %p [%d jobs %p]\n", sewing, cilk_rts_job, cilk_rts_jobs);
#endif
  sew_stitches_and_wait(sewing, cilk_rts_jobs, 1);
}

/**
 * Initializes the thread system and runs the provided main function
 *
 */
void cilk_begin_thread_system(void (*main)(void), int stacksize, int threadc, int jqueuelen, int fiberc) {
  size_t bytes = sew_it (
      NULL
    , stacksize // 64K stack per fiber
    , threadc   // 4 actual threads
    , jqueuelen // job queue length (very big)
    , fiberc    // 128 active fibers at a time
    , cilk_rts_run_main
    , main
  );
  void *sewing = malloc(bytes);
  sew_it (
      sewing
    , stacksize // 64K stack per fiber
    , threadc   // 4 actual threads
    , jqueuelen // job queue length (very big)
    , fiberc    // 128 active fibers at a time
    , cilk_rts_run_main
    , main
  );

  free(sewing);
}

#ifdef TEST
void start() {
  printf("Hello\n");
}

int main() {
  cilk_begin_thread_system(start, 65536, 4, 10, 1128);
  return 0;
}
#endif
