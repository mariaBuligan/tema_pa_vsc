build:
	gcc lan_party.c fct.c -o lanParty -lm
clean:
	rm -f lanParty
run:
	./lanParty c.in d.in r.out
