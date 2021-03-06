#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

int main() {

	void *virtual_base;
	int fd;
	void *h2p_lw;
	uint32_t init[8] = {0x6A09E667 , 0xBB67AE85 , 0x3C6EF372 , 0xA54FF53A, 0x510E527F , 0x9B05688C , 0x1F83D9AB , 0x5BE0CD19};

	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	
	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_A_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[0]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_B_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[1]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_C_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[2]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_D_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[3]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_E_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[4]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_F_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[5]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_G_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[6]; 

	h2p_lw = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_H_INIT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	*(uint32_t *)h2p_lw = init[7]; 


	// clean up our memory mapping and exit
	
	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}
