#line 1 "QEI.c"

#line 3 "QEI.c"
#line 4 "QEI.c"
#line 5 "QEI.c"
#line 6 "QEI.c"

void main(){
	INSTRUCTION_CYCLE = (OSCILLATOR)/d'4';
	RPM_CONSTANT_QEI = ((INSTRUCTION_CYCLE)/(d'1024' *d'2' *d'16' *d'1' )) * 60;
}
