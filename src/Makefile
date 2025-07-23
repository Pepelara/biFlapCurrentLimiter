
CC = sdcc

OPTION = -mmcs51
TARGET = biFlapCurrentLimiter.ihx
OUTDIR = build

INCLUDE = \
	-I.
	
LINK = 

${TARGET}: \
$(OUTDIR)/main.rel \
$(OUTDIR)/uart.rel 
	${CC} ${OPTION}  $^ -o $(OUTDIR)/${TARGET}

$(OUTDIR)/%.rel: %.c
	${CC} ${OPTION} -c $< -o $@
		
	
clean:
	rm ${OUTDIR}/*

flash:
	stcgal.py -p /dev/ttyUSB0 -b 115200 -P stc15 -t 11059 $(OUTDIR)/$(TARGET)
	#stcgal.py -p /dev/ttyUSB0 -b 300 $(OUTDIR)/$(TARGET)
