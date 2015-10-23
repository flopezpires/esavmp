all:
	gcc -c common.c reparation.c variation.c network.c pareto.c esavmp.c
	gcc -o esavmp common.o reparation.o variation.o network.o pareto.o esavmp.o -lm
clean:
	rm -rf *o esavmp
init: 
	rm -rf results/pareto_*
debug:
	gcc -g -c common.c reparation.c variation.c network.c pareto.c esavmp.c
	gcc -g -o esavmp common.o reparation.o variation.o network.o pareto.o esavmp.o -lm
