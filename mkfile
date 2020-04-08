<mkconfig

CFLAGS =
LDFLAGS =

SRC = `{ls *.c}
OBJ = ${SRC:%.c=%.o}
TGT = wavhd

all :Q: $TGT
	echo -n
run :VQ:
	./$TGT
$TGT : $OBJ
	$LD $LDFLAGS -o $target $prereq
%.o :V: %.c
	$CC $CFLAGS -c -o $target $prereq
%.c :

clean :V:
	rm -Rf $TGT *.o
install :V: $TGT
	cp -f $TGT $BIN
	chmod u+x $BIN/$TGT
