#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#define NUM_OF_SEGMENTS 8 // do not change bcz types
#define SIGNATURE_SIZE 64 // do not change bcz types
#define NUM_OF_ADDRS 1000

#define ROTL64(x, r) ((x << r) | (x >> (64 - r)))

// #define NUM_OF_THREADS 4

typedef struct {
    uint8_t segments[NUM_OF_SEGMENTS]; // u8 bcz 64/8 = 8
} BloomFilterSignature;

void read_logfile(uint64_t addresses[], int sz) {
    if(sz > NUM_OF_ADDRS) {printf("ERROR\n");}

    for(int i=0; i<sz; i++) {
        uint64_t address;
        scanf("%" SCNx64, &address);
        addresses[i] = address;
    }
}

void print_logfile(uint64_t addresses[], int sz) {
    for(int i=0; i<sz; i++) {
        printf("%" PRIx64 "\n", addresses[i]);
    }
}

uint64_t murmur_hash_64(uint64_t key, uint64_t seed) {
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;
    uint64_t h = seed ^ (8 * m);

    key *= m;
    key ^= key >> r;
    key *= m;

    h ^= key;
    h *= m;

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

void set_index(uint8_t *byte, int i) {
    *byte |= (1 << (i));
}

int get_index(uint8_t byte, int i) {
    return (byte & (1 << i)) != 0;
}

void generate_signature(uint64_t addresses[], int sz, BloomFilterSignature *signature) {
    for(int i=0; i<sz; i++) {
        for(int j=0; j<NUM_OF_SEGMENTS; j++) {
            uint64_t hash_val = murmur_hash_64(addresses[i], j);
            // printf("%" PRIu64 "\n", hash_val);
            int index = hash_val % (SIGNATURE_SIZE / NUM_OF_SEGMENTS);
            set_index(&(signature->segments[j]), index);
        }
    }
}

int search_signature(uint64_t address, BloomFilterSignature *signature) {
    for(int j=0; j<NUM_OF_SEGMENTS; j++) {
        uint64_t hash_val = murmur_hash_64(address, j);
        int index = hash_val % (SIGNATURE_SIZE / NUM_OF_SEGMENTS);
        if(get_index(signature->segments[j], index) == 0) return 0;
    }
    return 1;
}

void init_signature(BloomFilterSignature *signature) {
    for (int i = 0; i < NUM_OF_SEGMENTS; i++) {
        signature->segments[i] = 0;
    }
}

void test(uint64_t test_addresses[], BloomFilterSignature *signature) {
    for(int i=0; i<5; i++) {
        printf("%d\n", search_signature(test_addresses[i], signature));
    }
}

int main(int argc, char *argv[]) {
    BloomFilterSignature signature;

    init_signature(&signature);

    int log_sz = 0;
    // printf("Number of addresses in the logfile: ");
    scanf("%d", &log_sz);

    uint64_t addresses[NUM_OF_ADDRS];

    read_logfile(addresses, log_sz);

    generate_signature(addresses, log_sz, &signature);

    uint64_t test_addresses[10] = {
        0x1111111111111111, 0x1234123412341234, 0x4321432143214321, 0x1010101010101010, 0x0000000000000000,
        0x1335533189900998, 0x1267126790878790, 0x4578236389239056, 0x3758593625293746, 0x3476125395424263
    };

    test(test_addresses, &signature);

    return 0;
}