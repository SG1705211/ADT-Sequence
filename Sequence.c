#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This programs use dynamic memory to implement ADT.
struct sequence {
  int len;
  char **data;
};


// sequence_create() creates an sequence and returns a pointer to a new sequence
// effects: allocates memory 
// time: O(n)
struct sequence *sequence_create(void){
  struct sequence *a = malloc(sizeof(struct sequence));
  a->len = 0;
  a->data = NULL;
  return a;
}

// sequence_destroy(seq) free all memory in seq 
// effects: the memory is free
// time: O(1)
void sequence_destroy(struct sequence *seq){
  for (int i = 0; i < seq->len; i++) {
    free((seq->data)[i]);
  }
  free(seq->data);
  free(seq);
}

// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq){
  assert(seq);
  return seq->len;
}

// sequence_item_at(seq, pos) returns the element in seq with index seq.
// requires: 0 <= pos < length(seq)
// time: O(1)
const char *sequence_item_at(const struct sequence *seq, int pos){
  assert(seq);
  assert(pos >= 0 && pos < seq->len);
  return (seq->data)[pos];
}

// sequence_insert_at(seq, pos, s) inserts string s at index pos.
// requires: and 0 <= pos <= length(seq)
// effects: seq is modified
// time: O(n)
void sequence_insert_at(struct sequence *seq, int pos, const char *s){
  assert(pos >= 0 && pos <= seq->len);
  assert(seq);
  assert(s);
  char *str = malloc(sizeof(char) * (strlen(s)+1));
  for (int i = 0; i < strlen(s); i++) {
    str[i] = s[i];
  }
  str[strlen(s)] = '\0';
  (seq->len)++;
  seq->data = realloc(seq->data, seq->len * sizeof(char*));
  for (int i = seq->len - 1; i > pos; i--) {
    (seq->data)[i] = (seq->data)[i-1];
  }
  (seq->data)[pos] = str;
}

// sequence_remove_at(seq, pos) removes the element at position pos.
// requires: 0 <= pos < length(seq)
// effects: seq is modified
// time: O(n)
void sequence_remove_at(struct sequence *seq, int pos){
  assert(pos >= 0 && pos < seq->len);
  assert(seq);
  (seq->len)--;
  free((seq->data)[pos]);
  for (int i = pos; i < seq->len ; i++) {
    (seq->data)[i] = (seq->data)[i+1];
  }
  seq->data = realloc(seq->data, seq->len * sizeof(char*));
}

// sequence_equiv(seq1, seq2) returns true if seq1 and seq2 are identical seq.
// time: O(n * m)
bool sequence_equiv(const struct sequence *seq1, const struct sequence *seq2){
  assert(seq1);
  assert(seq2);
  if (seq1->len != seq2->len) {
    return false;
  }
  for (int i = 0 ; i < seq1->len; i++) {
    if (strcmp((seq1->data)[i], (seq2->data)[i]) != 0) {
      return false;
    }
  }
  return true;
}

// sequence_print(seq) prints out the whole sequence
// effects: prints out a message
// time: O(n * m)
void sequence_print(const struct sequence *seq) {
  assert(seq);
  if (seq->len == 0) {
    printf("[]\n");
    return;
  }
  printf("[%s", seq->data[0]);
  for (int i = 1; i < seq->len; i++){
    printf(",%s", seq->data[i]);
  }
  printf("]\n");
}

// sequence_filter(seq, f) removes all element i such that f(i) is false
// effects: modifies seq
// time: O(n) * O(f(i))
void sequence_filter(struct sequence *seq, bool (*f)(const char *)){
  assert(seq);
  assert(f);
  for (int i = 0; i < seq->len; i++) {
    if (!f(seq->data[i])){
      sequence_remove_at(seq,i);
    }
  }
}

// sequence_append(seq1, seq2) appends all strings from end of seq2
// into seq1.
// effects: seq1 is modified
// time: O(n + k * m)
void sequence_append(struct sequence *seq1, const struct sequence *seq2){
  assert(seq1);
  assert(seq2);
  for (int i = 0; i < seq2->len; i++) {
    sequence_insert_at(seq1,seq1->len, seq2->data[i]);
  }
}

// in_seq(a, seq) returns true if a is in seq and false otherwise.
// time： O(n)
bool in_seq(char* a, struct sequence *seq) {
  for (int i = 0; i < seq->len; i++) {
    if (strcmp(seq->data[i], a) == 0) {
      return true;
    }
  }
  return false;
}
// sequence_remove_dups(seq) removes all duplicates in seq.
// effects: modifies seq
// time: O(n^2 * m)
void sequence_remove_dups(struct sequence *seq){
  assert(seq);
  struct sequence *seq1 = sequence_create();
  int count = 0;
  for (int i = 0; i < seq->len; i++) {
    if (in_seq(seq->data[i], seq1)) {
      sequence_remove_at(seq,i);
    } else {
      sequence_insert_at(seq1, count, seq->data[i]);
    }
  }
  sequence_destroy(seq1);
}
