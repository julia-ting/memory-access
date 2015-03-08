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
   for (i = 0; i < CPU_NUM_FRAMES; i++) {
      if (rlt[i].pcb == NULL)
         return i;
   }

   pte_t *curr_pagetable;
   vpn_t curr_vpn;
   /*  See if there are any invalid frames  */
   for (i = 0; i < CPU_NUM_FRAMES; i++) {
      curr_pagetable = rlt[i].pcb->pagetable; 
      curr_vpn = rlt[i].vpn;
      if (curr_pagetable[curr_vpn].valid == 0) {
          return i;
      }
   }

   /* Clock sweep */
   int round;
   for (round = 0; round < 2; round++) {
       for (i = 0; i < CPU_NUM_FRAMES; i++) {
          curr_pagetable = rlt[i].pcb->pagetable;
          curr_vpn = rlt[i].vpn;
          if (curr_pagetable[curr_vpn].used) {
              curr_pagetable[curr_vpn].used = 0;
          } else {
              current_pagetable[i].used = 1;
              return i;
          }
       }
   }
      
   /* FIX ME : Problem 5 */
   /* IMPLEMENT A CLOCK SWEEP ALGORITHM HERE */

   /* If all else fails, return a random frame */
   return rand() % CPU_NUM_FRAMES;
}
