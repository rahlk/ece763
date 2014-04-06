# Main target
houghcircles: houghcircles.c
	cc houghcircles.c -o houghcircles -I/home/rkrsn/Fedora64/hdr \
	/home/rkrsn/Fedora64/ifslib/libflip.a /home/rkrsn/Fedora64/ifslib/libiptools.a \
	/home/rkrsn/Fedora64/ifslib/libifs.a \
	/home/rkrsn/Fedora64/ifslib/libflip.a -lm  -std=gnu99
	houghcircles
	rm houghcircles
	ifsview -i edge.ifs
#	vidscale -i out.ifs -o angio_out.ifs
#	any2any -i angio_out.ifs -o angio_out.jpg
houghcircles1: hCircFuzzy.c
	cc houghcircles.c -o hCircFuzzy -I/home/rkrsn/Fedora64/hdr \
	/home/rkrsn/Fedora64/ifslib/libflip.a /home/rkrsn/Fedora64/ifslib/libiptools.a \
	/home/rkrsn/Fedora64/ifslib/libifs.a \
	/home/rkrsn/Fedora64/ifslib/libflip.a -lm  -std=gnu99
	hCircFuzzy
#	vidscale -i out.ifs -o angio_out.ifs
#	any2any -i angio_out.ifs -o angio_out.jpg
houghcircles2: houghMultCircles.c
	cc houghMultCircles.c -o houghMultCircles -I/home/rkrsn/Fedora64/hdr \
	/home/rkrsn/Fedora64/ifslib/libflip.a /home/rkrsn/Fedora64/ifslib/libiptools.a \
	/home/rkrsn/Fedora64/ifslib/libifs.a \
	/home/rkrsn/Fedora64/ifslib/libflip.a -lm  -std=gnu99
	clear all
	houghMultCircles
#	vidscale -i out.ifs -o angio_out.ifs
#	any2any -i angio_out.ifs -o angio_out.jpg

