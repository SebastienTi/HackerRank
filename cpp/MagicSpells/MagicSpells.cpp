#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

  /* Enter your code here */
  
  /* Common spell types*/
  if (auto* fire = dynamic_cast<Fireball*>(spell)) {
      fire->revealFirepower();
  } else if(auto* frost = dynamic_cast<Frostbite*>(spell)) {
      frost->revealFrostpower();
  } else if (auto* water = dynamic_cast<Waterbolt*>(spell)) {
      water->revealWaterpower();
  } else if(auto* thunder = dynamic_cast<Thunderstorm*>(spell)) {
      thunder->revealThunderpower();
  } else {
      /* Other spells type*/
      
      auto scrollName = spell->revealScrollName();
      auto spellJournal = SpellJournal::read();
      
      /* Creation of the matrix to contain max length */
      vector<vector<int>> matrix(scrollName.size() + 1, vector<int>(spellJournal.size() + 1));
      
      for(int i = 0; i < scrollName.size(); i++) {
          for(int j = 0; j < spellJournal.size(); j++) {
              /* Check if a character matches with the other */
              if(scrollName[i] == spellJournal[j]) {
                  /* Increase actual value and save it in the next cell */
                  matrix[i+1][j+1] = matrix[i][j] + 1; 
              } else {
                  /* Find highest value stored and save it in the next cell */
                  matrix[i+1][j+1] = max(matrix[i][j+1], matrix[i+1][j]);
              }
          }
      }
      /* Print the latest value found */
      cout << matrix[scrollName.size()][spellJournal.size()] << endl;
  }

}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
