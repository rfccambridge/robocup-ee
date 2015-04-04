﻿class QEI_Handler {
private:
	int directions[] = {0,0,0,0};
	int counts[] = {0,0,0,0};
		
public:
	enum Wheel {
		WHEEL_LB,
		WHEEL_RB,
		WHEEL_LF,
		WHEEL_RF
	};
	
	void handleQEI(Wheel wheel)
	{
		static int lookuptable[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
		static int enc_val[] = {0,0,0,0};
		
		enc_val[wheel] = enc_val[wheel] << 2;
		enc_val[wheel] = enc_val[wheel] | ((PIND & (0b11 << wheel)) >> wheel);
		
		counts[wheel] = counts[wheel] + lookuptable[enc_val[wheel] & 0b1111];
	}
	
	};