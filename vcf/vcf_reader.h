#ifndef VCF_READER_H
#define VCF_READER_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <commons/file_utils.h>
#include <commons/log.h>
#include <containers/list.h>

#include "vcf_util.h"
#include "vcf_file_structure.h"
#include "vcf_file.h"
#include "vcf_read.h"
#include "vcf_batch.h"

extern int mmap_vcf;

enum VCF_Field { CHROM, POS, ID, REF, ALT, QUAL, FILTER, INFO, FORMAT, SAMPLE };

typedef struct {
    vcf_record_t *current_record;
    vcf_header_entry_t *current_header_entry;
    vcf_batch_t *current_batch;
    
    enum VCF_Field current_field;
    
    size_t num_samples;
    size_t num_records;
    
    int store_samples;
    int self_contained;
} vcf_reader_status;

int execute_vcf_ragel_machine(char *p, char *pe, list_t *batches_list, size_t batch_size, vcf_file_t *file, vcf_reader_status *status);

int vcf_ragel_read(list_t *batches_list, size_t batch_size, vcf_file_t *file, int read_samples);

int vcf_light_read(list_t *batches_list, size_t batch_size, vcf_file_t *file);


vcf_reader_status *new_vcf_reader_status(size_t batch_size, int store_samples, int self_contained);

#endif
