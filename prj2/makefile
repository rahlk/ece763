# Main target
angio: main_ang.c
	cc main_ang.c -o main_ang -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_ang
	ifsview -i out.ifs
	vidscale -i out.ifs -o angio_out.ifs
	any2any -i angio_out.ifs -o angio_out.jpg
lymph: main_lymph.c
	cc main_lymph.c -o main_lymph -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_lymph
	ifsview -i out.ifs
	vidscale -i out.ifs -o lymph_out.ifs
	any2any -i lymph_out.ifs -o lymph_out.jpg
angio128:main_ang1.c
	cc main_ang1.c -o main_ang1 -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_ang1
	ifsview -i out.ifs
	vidscale -i out.ifs -o angio_out.ifs
	any2any -i angio_out.ifs -o angio_out.jpg
taj:main_taj.c
	cc main_taj.c -o main_taj -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_taj
	ifsview -i out.ifs
	vidscale -i out.ifs -o taj_out.ifs
	any2any -i taj_out.ifs -o taj_out.jpg
MRI:main_mri.c
	cc main_mri.c -o main_mri -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_mri
	ifsview -i out.ifs
	vidscale -i out.ifs -o mri_out.ifs
	any2any -i mri_out.ifs -o mri_out.jpg
gNoise:main_synth1.c
	cc main_synth1.c -o main_synth1 -I/home/rahul/Ubuntu64/hdr \
	/home/rahul/Ubuntu64/ifslib/libflip.a /home/rahul/Ubuntu64/ifslib/libiptools.a \
	/home/rahul/Ubuntu64/ifslib/libifs.a \
	/home/rahul/Ubuntu64/ifslib/libflip.a -lm  -std=gnu99
	main_synth1
	ifsview -i out.ifs
	vidscale -i out.ifs -o mri_out.ifs
	any2any -i mri_out.ifs -o mri_out.jpg


	

