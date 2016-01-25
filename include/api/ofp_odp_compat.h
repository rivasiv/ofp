/* Copyright (c) 2015, ENEA Software AB
 * Copyright (c) 2015, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#ifndef __OFP_ODP_COMPAT__
#define __OFP_ODP_COMPAT__

#if ODP_VERSION == 102
#include "linux.h"
#else
#include "odp/helper/linux.h"
#endif /* odp_version == 102 */

#if ODP_VERSION < 105
typedef uint64_t odp_time_t;
#endif /* ODP_VERSION < 105 */

#if ODP_VERSION < 104 && ODP_VERSION > 101
#define odp_cpumask_default_worker(cpumask, num_workers) odp_cpumask_def_worker(cpumask, num_workers)
#elif ODP_VERSION < 102
#define odp_cpumask_default_worker(cpumask, num_workers) odp_cpumask_count(cpumask)
#define odp_init_local(x) odp_init_local()
#define ODP_THREAD_WORKER 0
#define ODP_THREAD_CONTROL 1
typedef int64_t odp_thread_type_t;
#endif /* ODP_VERSION < 104 && ODP_VERSION > 101 */

static inline int ofp_linux_pthread_create(odph_linux_pthread_t *thread_tbl,
                             const odp_cpumask_t *mask_in,
                             void *(*start_routine)(void *), void *arg,
                             odp_thread_type_t thr_type)
{
       (void) thr_type;
#if ODP_VERSION == 100
       odph_linux_pthread_create(thread_tbl,
                                 mask_in,
                                 start_routine,
                                 arg);
       return 1;
#else
       return odph_linux_pthread_create(thread_tbl,
                                 mask_in,
                                 start_routine,
                                 arg
#if ODP_VERSION >= 106
                                , thr_type
 #endif
                                );
#endif /* ODP_VERSION == 100 */
}

#endif