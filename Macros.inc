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
;Configura cualquiera de los pines como salida
;-------------------------------------------------	
_pin_m_out    macro TRISX,PORTX,LATX,ANSELX,RXX
		    banksel PORTX
		    bcf	    PORTX,RXX
		    banksel ANSELX
		    bcf	    ANSELX,RXX
		    banksel TRISX
		    bcf	    TRISX,RXX
		    endm

;-------------PIN MODE INPUT---------------------
;Configura cualquiera de los pines como entrada
;------------------------------------------------		    
_pin_m_in	    macro TRISX,PORTX,LATX,ANSELX,RXX
		    banksel PORTX
		    bcf	    PORTX,RXX
		    banksel ANSELX
		    bcf	    ANSELX,RXX
		    banksel TRISX
		    bsf	    TRISX,RXX
		    endm
_pin_write_high	    macro TRISX,PORTX,LATX,ANSELX,RXX
		    banksel LATX
		    bsf	LATX,RXX
		    endm
_pin_write_low	    macro TRISX,PORTX,LATX,ANSELX,RXX
		    banksel LATX
		    bcf	LATX,RXX
		    endm
_filebit_write_high macro file,bit
		    banksel file
		    bsf	file,bit
		    endm
_filebit_write_low  macro file,bit
		    banksel file
		    bcf	file,bit
		    endm
_if_pin_high_do_else_goto   macro	TRISX,PORTX,LATX,ANSELX,RXX,label
			    pagesel	label
			    banksel	PORTX
			    btfss	PORTX,RXX
			    goto	label
			    endm
_if_pin_low_do_else_goto    macro	TRISX,PORTX,LATX,ANSELX,RXX,label
			    pagesel	label
			    banksel	PORTX
			    btfsc	PORTX,RXX
			    goto	label
			    endm			    
_if_filebit_high_do_else_goto   macro	file,bit,label
				pagesel	label
				banksel	file
				btfss	file,bit
				goto	label
				endm
_if_filebit_low_do_else_goto	macro	file,bit,label
				pagesel	label
				banksel	file
				btfss	file,bit
				goto	label
				endm			    
			
		

		
		
		
		
	

;selecciona el banco 0
bank0 	macro
	banksel STATUS		
	bcf STATUS,BSR1
			bcf	STATUS,BSR0
		endm

;selecciona el banco 1		
bank1	macro
	banksel STATUS
			bcf STATUS,BSR1
			bsf	STATUS,BSR0
		endm
		
suma	macro	R1,R2,R3
	banksel R1
	movfw	R1
	addwf	R2,w
	movwf	R3
	banksel STATUS
	btfsc	STATUS,C
	movlw	0x01
	banksel R3
	movwf	R3+1
	
	endm
	

;si el bit del registro es 1 continua en la siguiente instruccion		
ifbitset	macro	file,bit
				btfsc	file,bit
		endm

;si el bit del registro es 0 continua en la siguiente instruccion			
ifbitclear	macro	file,bit
				btfss	file,bit
			endm
			
;mueve una constante a un registro			
move_l_f	macro	file,lit
				movlw	lit
				movwf	file
			endm
;mueve el contenido del registro fs (source) a fd (destiny)			
move_fs_fd	macro	fs,fd
				movf	fs,w
				movwf	fd
			endm									
			
			
								
bin2BCD	macro 	reg
		movf		reg,w
		movwf		multil
		bcf		STATUS,C
		rlf		multil,f
		ifbitclear	STATUS,C
		goto		$+3
		movlw		0x01
		movwf		multih
	
		movf		multih,w
		movwf		TEM2
		movf		multil,w
		movwf		TEM0
		call		convertBCD
		
		
		MOVLW		0x30		; load ASCII offset
		ADDWF		TEM2,F	; convert hundreds to ASCII
		ADDWF		TEM1,F	; convert tens to ASCII
		ADDWF		TEM0,F	; convert ones to ASCII

		MOVF		TEM2,W	; carga las centenas
		CALL		LCD_Dato	; and send to display
		MOVLW		'.'		; load point code
		CALL		LCD_Dato	; and output
		MOVF		TEM1,W	; load hundreds code
		CALL		LCD_Dato	; and send to display
		MOVF		TEM0,W	; load tens code
		CALL		LCD_Dato	; and output
		clrf		multih
		clrf		multil
		
			
		endm




