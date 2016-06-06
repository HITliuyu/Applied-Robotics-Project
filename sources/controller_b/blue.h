/* 
 * File:   blue.h
 * Author: guido
 *
 * Created on 4 novembre 2015, 20.02
 */

#ifndef BLU_MASTER_H
#define	BLU_MASTER_H




typedef struct {
           
    uint8_t reference_speed;    
   
}__attribute__((__packed__)) MSPACKET;

typedef struct {
   
    
    uint32_t system_time;
    
    float speed;
   
}__attribute__((__packed__)) SMPACKET;

/*
typedef struct {
   
    uint8_t port;
    
    int8_t velocity;

    uint8_t brake;

    uint32_t nsamples;
   
}__attribute__((__packed__)) MSPACKET;

typedef struct {
   
    
    uint32_t system_time;
    
    int32_t degree_counter;
   
}__attribute__((__packed__)) SMPACKET;
*/




#endif	/* BLU_MASTER_H */

