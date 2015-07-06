.PHONY:all
.PHONY:clean

TARGETS = doc8126_ATtiny13A_Complete.pdf 8126S_ATtiny13A_Summary.pdf avr-libc-user-manual-1.8.0.pdf

all: $(TARGETS)

doc8126_ATtiny13A_Complete.pdf:
	wget -N http://www.atmel.com/Images/doc8126.pdf -O $@

8126S_ATtiny13A_Summary.pdf:
	wget -N http://www.atmel.com/Images/8126S.pdf -O $@

avr-libc-user-manual-1.8.0.pdf:
	wget -N http://savannah.nongnu.org/download/avr-libc/avr-libc-user-manual-1.8.0.pdf.bz2
	bunzip2 avr-libc-user-manual-1.8.0.pdf.bz2

clean:
	rm -f $(TARGETS)
