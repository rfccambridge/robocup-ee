/*
 * CppDemo.cpp
 *
 * Created: 5/25/2015 11:08:35 AM
 *  Author: Erik
 */ 

#include <avr/io.h>
#include "sweeper.cpp"

int main(void)
{
    Sweeper sw = Sweeper();
	
	while(1) {
		sw.sweep(500);
	}
}