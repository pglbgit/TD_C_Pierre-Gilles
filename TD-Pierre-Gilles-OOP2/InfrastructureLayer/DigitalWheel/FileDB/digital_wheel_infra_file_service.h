#ifndef DW_INFRA_FILE_SERVICE_H
#define DW_INFRA_FILE_SERVICE_H

extern int DigitalWheelInfraFileService_open(char *name);
extern void DigitalWheelInfraFileService_append(digital_wheel record);
extern void DigitalWheelInfraFileService_close(void);
extern digital_wheel DigitalWheelInfraFileService_get_nth(int rank);
#endif