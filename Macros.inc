;LIBRERIA DE MACROS PARA PIC GAMA MEDIA ENHANCED 16F1XXX 

	errorlevel    -302  ;ELIMINA EL WARNING DE CAMBIO DE BANCOS
	
;****************DEFINICIONES************************** 
	
_HIGH	EQU 0x1
_LOW	EQU 0x0
	
#define	_RA0 TRISA,PORTA,LATA,ANSELA,RA0
#define	_RA1 TRISA,PORTA,LATA,ANSELA,RA1
#define	_RA2 TRISA,PORTA,LATA,ANSELA,RA2
#define	_RA3 TRISA,PORTA,LATA,ANSELA,RA3	
#define	_RA4 TRISA,PORTA,LATA,ANSELA,RA4
#define	_RA5 TRISA,PORTA,LATA,ANSELA,RA5
#define	_RA6 TRISA,PORTA,LATA,ANSELA,RA6
#define	_RA7 TRISA,PORTA,LATA,ANSELA,RA7	

#define	_RB0 TRISB,PORTB,LATB,ANSELB,RB0
#define	_RB1 TRISB,PORTB,LATB,ANSELB,RB1
#define	_RB2 TRISB,PORTB,LATB,ANSELB,RB2	
#define	_RB3 TRISB,PORTB,LATB,ANSELB,RB3
#define	_RB4 TRISB,PORTB,LATB,ANSELB,RB4
#define	_RB5 TRISB,PORTB,LATB,ANSELB,RB5	
#define	_RB6 TRISB,PORTB,LATB,ANSELB,RB6
#define	_RB7 TRISB,PORTB,LATB,ANSELB,RB7

;********************************************************
	

;********CONFIGURACION DE PINES DEL MICRO****************

;-------------PIN MODE OUTPUT---------------------
;Configura cualquiera de los pines como SALIDA
;-------------------------------------------------	
_pin_m_out	    macro   TRISX,PORTX,LATX,ANSELX,RXX
		    banksel PORTX
		    bcf	    PORTX,RXX
		    banksel ANSELX
		    bcf	    ANSELX,RXX
		    banksel TRISX
		    bcf	    TRISX,RXX
		    endm

;-------------PIN MODE INPUT---------------------
;Configura cualquiera de los pines como ENTRADA
;------------------------------------------------		    
_pin_m_in	    macro   TRISX,PORTX,LATX,ANSELX,RXX
		    banksel PORTX
		    bcf	    PORTX,RXX
		    banksel ANSELX
		    bcf	    ANSELX,RXX
		    banksel TRISX
		    bsf	    TRISX,RXX
		    endm
		    
;-------------PIN HIGH---------------------------
;Coloca un estado ALTO en el PIN seleccionado
;------------------------------------------------		    
_pin_hi		    macro   TRISX,PORTX,LATX,ANSELX,RXX
		    banksel LATX
		    bsf	    LATX,RXX
		    endm
		    
;-------------PIN LOW---------------------------
;Coloca un estado BAJO en el PIN seleccionado
;-----------------------------------------------		    
_pin_lo		    macro   TRISX,PORTX,LATX,ANSELX,RXX
		    banksel LATX
		    bcf	    LATX,RXX
		    endm
		    
;-------------PORT MODE OUTPUT---------------------
;Configura un PUERTO completo como SALIDA
;-------------------------------------------------		    
_port_m_out	    macro   PORTX
		    banksel PORTX
		    clrf    PORTX
		    banksel ANSELX
		    clrf    ANSELX
		    banksel TRISX
		    clrf    TRISX
		    endm

;-------------PORT MODE INPUT---------------------
;Configura un PUERTO completo como ENTRADA
;-------------------------------------------------		    
_port_m_in	    macro   PORTX
		    banksel PORTX
		    clrf    PORTX
		    banksel ANSELX
		    clrf    ANSELX
		    banksel TRISX
		    movlw   B'11111111'
		    movwf   TRISX
		    endm
		    
;******************************************************	

;********MANEJO DE REGISTROS DEL MICRO*****************
		    
;-------------FILE REGISTER BIT HIGH-----------------------
;Coloca un estado ALTO en el BIT del REGISTRO seleccionado
;----------------------------------------------------------		    
_fb_hi		    macro   file,bit
		    banksel file
		    bsf	    file,bit
		    endm
		    
;-------------FILE REGISTER BIT LOW------------------------
;Coloca un estado BAJO en el BIT del REGISTRO seleccionado
;----------------------------------------------------------		    
_fb_lo		    macro   file,bit
		    banksel file
		    bcf	    file,bit
		    endm

;-------------FILE REGISTER LITERAL------------------------
;Carga un valor LITERAL en el REGISTRO seleccionado
;----------------------------------------------------------		    
_fb_li		    macro   file,value
		    banksel file
		    movlw   value
		    movwf   file
		    endm

;**********************************************************		    
		    
;*****************FLOW CODE INSTRUCTIONS*******************

;-------------IF PIN HIGH GOTO LABEL------------------------
;SI el PIN se encuentra en ALTO GOTO label
;-----------------------------------------------------------		    
_if_pin_hi_go	    macro   TRISX,PORTX,LATX,ANSELX,RXX,label
		    pagesel label
		    banksel PORTX
		    btfsc   PORTX,RXX
		    goto    label
		    endm
		    
;-------------IF PIN LOW GOTO LABEL-------------------------
;Si el PIN se encuentra en BAJO GOTO label
;-----------------------------------------------------------		    
_if_pin_lo_go	    macro   TRISX,PORTX,LATX,ANSELX,RXX,label
		    pagesel label
		    banksel PORTX
		    btfss   PORTX,RXX
		    goto    label
		    endm
		    
;-------------IF FILE REGISTER BIT HIGH GOTO LABEL----------
;Si el BIT del FILE REGISTER se encuentra en ALTO GOTO label
;-----------------------------------------------------------
_if_fb_hi_go	    macro   file,bit,label
		    pagesel label
		    banksel file
		    btfsc   file,bit
		    goto    label
		    endm
		
;-------------IF FILE REGISTER BIT LOW GOTO LABEL----------
;Si el BIT del FILE REGISTER se encuentra en BAJO GOTO label
;-----------------------------------------------------------		    
_if_fb_lo_go	    macro   file,bit,label
		    pagesel label
		    banksel file
		    btfss   file,bit
		    goto    label
		    endm			    
			
		

		
		
		
		
	



