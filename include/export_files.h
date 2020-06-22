#ifndef EXPORT_FILES_H_INCLUDED
#define EXPORT_FILES_H_INCLUDED

int export_files(struct CONFIG *my_config, struct STATE *my_state, char *output_directory);
int export_csv(struct STATE *my_state , char *file_name);
int write_file(struct STATE *my_state, FILE *file);

#endif // EXPORT_FILES_H_INCLUDED
