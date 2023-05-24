build:
	gcc lan_party.c fct.c -o lanParty
clean:
	rm -f lanParty
run:
	./lanParty c.in d.in r.out
