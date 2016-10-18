scanner: scanner.l
	flex scanner.l
	gcc lex.yy.c -o ./main

extract_cmds: primative_test_gfx.txt
	sed 's/[]0-9.[-]/ /g' ./primative_test_gfx.txt | sed 's/\/[^[:space:]]*/ /g' - | sed 's/ /\n/g' - | sort -u > ./primative_test_gfx_cmds.txt

clean:
	rm -f main
	rm -f lex.yy.c

