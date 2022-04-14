// SUCCESS indicates successful execution of the function.
extern const int SUCCESS;
// COLLISION indicates that a hash collision has occurred.
extern const int COLLISION;
// ALREADY_STORED indicates that a value was already stored in the hashtable.
extern const int ALREADY_STORED;
// NOT_STORED indicates that a value was not stored in the hashtable.
extern const int NOT_STORED;

// a hashtable storing strings
struct hashtable;

// ht_create(hash_func, hash_length) creates a new string hashtable of fixed
//   length hash_length with hash_func as hash function.
// effects:  allocates heap memory; client must call ht_destroy
// requires: hash_length must be positive
// time:     O(n), where n is the length of ht
struct hashtable *ht_create(int (*hash_func)(const char *, int),
                            int hash_length);

// ht_destroy(ht) frees all resources allocated by the hashtable ht.
// effects: invalidates ht
// time:    O(n), where n is the length of ht
void ht_destroy(struct hashtable *ht);

// ht_insert(ht, str) inserts the string str into the hashtable ht. The
//   function returns
//   * SUCCESS if str has been inserted into ht,
//   * COLLISION if str could not be inserted due to a hash collision, or
//   * ALREADY_STORED if str was already stored in ht.
// time: O(s), where s is the length of str
int ht_insert(struct hashtable *ht, const char *str);

// ht_remove(ht, str) removes the string str from the hashtable ht. The
//   function returns
//   * SUCCESS if str has been removed from ht, or
//   * NOT_STORED if str was not stored in ht.
// time: O(s), where s is the length of str
int ht_remove(struct hashtable *ht, const char *str);

// ht_print(ht) prints the content of hashtabe ht to the console.
// effects: creates output
// time:    O(n * s), where n: length of ht; s: maximum length of any string
void ht_print(const struct hashtable *ht);
