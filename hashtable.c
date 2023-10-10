#include <stdio.h>
#include <string.h>

/* What are the functions we need for this?
 * We need a hash function(string) -> bucket_index
 *  We need a bucket data structure. Where bucket[i] = ptr to linked list
 */

// What is a good hash function?
// Words are differentiated by their characters and by the order
// of their characters. So lets hash on those properties
// Is there a math operation where the order matters.
long long hash(char *string, long long n_buckets) {
  // Well lets consider
  // xp + yp^2 = yp + xp^2 ?
  // And consider this for x,y are natural numbers
  // This is true when
  // - x = y
  // Hmm I don't have much more to say on this
  // Lets try an example
  // Say p = 3
  // 3x + 9y = 3y + 9x
  // p (xp - x) = p (yp - y) ?
  // If p were 4
  // 4 * ? = 16
  // 12x = 16 ?  and x is integer?
  // Nope
  // Lets make it so that
  // 12x = 48
  // 4(3y) = 48
  long p = 23;
  long long pow_p = 1;
  long hash = 0;
  for (unsigned long i = 0; i < strlen(string); i++) {
    hash = (hash + string[i] * p) % n_buckets;
    pow_p = (pow_p * p) % n_buckets;
  }
  return hash;
}
