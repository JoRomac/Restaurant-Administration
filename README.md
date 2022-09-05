# Restaurant-Administration
Application for booking managment

Pristup Bazi:
Pristup bazi podataka (Access) je preko ODBC source. U Control Panelu se dodaje ODBC source (System DNS) koji pokazuje na Access bazu podataka.
Ime baze podataka je RestaurantDb. Napomena: korisiti 32-bitnnu verziju ODBC-a.


Korištenje projekta:
Kada se pokrene aplikacija otvara se login dialog koji traži unos korisničkog imena i lozinke (admin, 456) za pristum glavnom dijelu aplikacije.
Nakon ispravno unešenih korisničkih podataka otvara se glavni dialog koji se sastoji od dva button-a (Booking Manager), od kojih jedan nudi pristup uređivanju korisnika aplikacije,
a drugi uređivanje rezervacija.


Uređivanje rezervacija (Booking Manager):
Dialog uređivanja rezervacija se sastoji od list kontrole, date time picker,
5 button-a (add reservation, update reservation, remove reservation, save as pdf, main menu)
i dvije statičke kontrole.

Kada se otvori dialog uređivanja rezervacija, unutar list kontrole će se pojaviti sve rezervacije trenutnog dana. Na odabir datuma pomoću date time picker kontrole
pojavit će se rezervacije za odabrani datum te će datum biti prikazan u jednoj od statičkih kontrola a u drugoj ukupan broj gostiju odabranog dana.
Navedeni button add reservation omogućuje dodavanje nove rezervacije s potrebnim detaljima gosta, a update reservation će omogućiti izmjenu samo onih bitnih detalja
rezervacije kao što je dan, sat, broj ljudi ili nekakva prigoda. Remove button jednostavno će izbrisati onu rezervaciju na koju se klikne unutra list kontrole.
Save as pdf button omogućuje ispis rezervacija na odabrani datum te kreira pdf datoteku.


Uređivanje korisnika (Manage Users):
Klikom na button Manage Users otvara se dialog sa list kontrolom koja će ispisati sve korisnike aplikacije koji se nalaze u bazi podataka.
Omogućene se opcije brisanja i dodavanja novih korisnika.
