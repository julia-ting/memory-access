#include <stdlib.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */
pfn_t get_free_frame(void) {
   int i;

   /* See if there are any free frames */
   for (i = 0; i < CPU_NUM_FRAMES; i++)
      if (rlt[i].pcb == NULL)
         return i;

   for (i = 0; i < CPU_NUM_PTE; i++) {
      if (current_pagetable[i].valid == 0) {
          current_pagetable[i].used = 1;
          current_pagetable[i].valid = 1;
        // do i mark it as valid?
          return i;
      }
   }
   for (i = 0; i < CPU_NUM_PTE; i++) {
      if (current_pagetable[i].used) {
          current_pagetable[i].used = 0;
      } else {
          current_pagetable[i].used = 1;
          return i;
      }
   }
   for (i = 0; i < CPU_NUM_PTE; i++) {
       if (!(current_pagetable[i].used)) {
           current_pagetable[i].used = 1;
           return i;
       } else {
           current_pagetable[i].used = 0;
       }
   }
      
   /* FIX ME : Problem 5 */
   /* IMPLEMENT A CLOCK SWEEP ALGORITHM HERE */

   /* If all else fails, return a random frame */
   return rand() % CPU_NUM_FRAMES;
}
