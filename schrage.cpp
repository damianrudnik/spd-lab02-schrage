#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <new>
#include <vector>
#include <ctime>
#include <queue>

double t;// czas wykonywania algorytmu 
using namespace std;

struct Zadanie {
    int kolejnosc;//kolejnosc zadania
    int r;//czas przygotowania
    int p;//czas na maszynie
    int q;//czas stygniecia
};

struct PorownajZadania{
    bool operator ()( const Zadanie & Zadanie1, const Zadanie & Zadanie2 ) {
        //kolejność - rosnąco
        if( Zadanie1.r > Zadanie2.r ) return true;
        if( Zadanie1.r < Zadanie2.r ) return false;
        if( Zadanie1.q < Zadanie2.q ) return true;
        if( Zadanie1.q > Zadanie2.q ) return false;
        return false;
    }
};

typedef priority_queue < Zadanie, std::vector < Zadanie >, PorownajZadania > KolejkaZadan;

void WstawZadanie( KolejkaZadan & kp, int kolejnosc, int r, int p, int q){
    Zadanie NoweZadanie;
    NoweZadanie.kolejnosc = kolejnosc;
    NoweZadanie.r = r;
    NoweZadanie.p = p;
    NoweZadanie.q = q;
    kp.push( NoweZadanie );
}

void WyswietlKolejke(KolejkaZadan kp) {
    while(kp.size() > 0){
        Zadanie odczytane = kp.top();
        kp.pop();
        cout << odczytane.kolejnosc << " "; 
    }
    cout << '\n';
}

unsigned int max(unsigned int x, unsigned int y){ return (x<=y)?y:x; }
unsigned int min(unsigned int x, unsigned int y){ return (x<=y)?x:y; }

/*istream& operator>> (istream& wejscie, Zadanie& zad){
    zad.kolejnosc = ++iIndexZadan;
    wejscie >> zad.r >> zad.p >> zad.q;
    return wejscie;
}*/
ostream& operator<< (ostream& wyjscie, const Zadanie& zad){
    cout << zad. kolejnosc << ": " << zad.r << " - " << zad.p << " - " << zad.q << endl; 
    return wyjscie;
}
int cmax(KolejkaZadan & kp){
    unsigned int t=0,u=0;
    while (!kp.empty()){
        cout<<kp.top();
        t=max(t,kp.top().r)+kp.top().p;
        u=max(u,t+kp.top().q);
        kp.pop();
    }
    return u;
}

// sortowanie przez kopcowanie tablicy zadan z wyborem 1-r, 2-p, 3-q
void heapsort(Zadanie arr[], unsigned int N, int rpq){ //http://www.codecodex.com/wiki/Heapsort#C.2B.2B
    unsigned int n = N, i = n/2, parent, child;  
    Zadanie t;
    
    for (;;) { /* Loops until arr is sorted */  
        if (i > 0) { /* First stage - Sorting the heap */  
            i--;           /* Save its index to i */  
            t = arr[i];    /* Save parent value to t */  
        } else {     /* Second stage - Extracting elements in-place */  
            n--;           /* Make the new heap smaller */  
            if (n == 0) return; /* When the heap is empty, we are done */  
            t = arr[n];    /* Save last value (it will be overwritten) */  
            arr[n] = arr[0]; /* Save largest value at the end of arr */  
        }  
    
        parent = i; /* We will start pushing down t from parent */  
        child = i*2 + 1; /* parent's left child */  
    
        /* Shift operation - pushing the value of t down the heap */  
        while (child < n) { 
            if (rpq==1){
                if (child + 1 < n  &&  arr[child + 1].r > arr[child].r) {  
                    child++; /* Choose the largest child */  
                } 
            }else if (rpq == 2){
                if (child + 1 < n  &&  arr[child + 1].p > arr[child].p) {  
                    child++; /* Choose the largest child */  
                }
            }else if (rpq == 3){
                if (child + 1 < n  &&  arr[child + 1].q > arr[child].q) {  
                    child++; /* Choose the largest child */  
                }
            }
            //if (child + 1 < n  &&  arr[child + 1] > arr[child]) {  
            //    child++; /* Choose the largest child */  
            //}  
            if (rpq==1){
                if (arr[child].r > t.r) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                }
            }else if (rpq == 2){
                if (arr[child].p > t.p) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }else if (rpq == 3){
                if (arr[child].q > t.q) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }
        }  
        arr[parent] = t; /* We save t in the heap */  
    }  
}
void swap(Zadanie *x,  Zadanie *y)  { Zadanie z;  z=*x; *x=*y; *y=z; }
void check(int m, Zadanie TabG[]){
    int k = m/2;
    if (k){
        if(TabG[k].q < TabG[m].q){
            swap(TabG[k],TabG[m]);
            check(k,TabG);
        }
    }
}
void sleave(int i, int m, Zadanie TabG[]){
    int k=i<<1,u;
    if (k > m) return;
    u=((k < m) && (TabG[k].q < TabG[k+1].q))?(k+1):k;
    if (TabG[u].q>TabG[i].q){
        swap(TabG[u],TabG[i]);
        sleave(u, m, TabG);
    }
}

void fdr(KolejkaZadan & kp){
    //heapsort(Tab,rozmiar,1);//wstepne sortowanie po r
    //Zadanie *TabG = new Zadanie[rozmiar];//talica zadan gotowych
    /*int t=0,k=0,cmaks=0;
    int e=2, m=1;
    Zadanie j;
    while(m||(e<=rozmiar)){
        while(e<=rozmiar){
            if ( Tab[e].r<=t){
                TabG[++m] = TabG[e++];
                check(m,TabG);
            }else break;
            if (m){
                j=TabG[1];
                Tab[++k] = j;
                t+=Tab[j].p;
                _c[j]=t;

            }
        }
    }

    
    while() {
        while( && Tab[j].r <= t){
            e = Tab[j].r;
            
        }
    }
    */
    /*for (unsigned int i = 0; i < rozmiar; i++){
        arr[i] = Tab[i].kolejnosc;
    }*/
    //delete[] TabG;

}

void intime(){ 
  t=clock();
}

void showtime(){ 
  t=clock()-t; 
  cout <<"\nWszystkie operacje zajely: " << ((double)t)/CLOCKS_PER_SEC << " s.\n\n";
}

string itos(int a) {
    string sign = a<0?"-":"";
    string result = a>0?string(1,(a%10+'0')):string(1,((a=-a)%10+'0'));
    (a/=10)>0?result=itos(a)+result:result;
    return sign+result;
}

int main(){
    unsigned int LiczbaZadan = 0;
    string filename;
    int tab[9] = {32,687,1299,1399,3487,3659,6918,6936,72853};

    cout<<"Generuje odpowiedzi dla wszystkich plikow.\n###############################################\n\n";
    intime();

    for (int iNrPliku = 1; iNrPliku<=1;iNrPliku++){ // odczyt, szeregowanie i zapis wyniku do plikow

        KolejkaZadan Kolejka;
        Zadanie Zad;
        filename = itos(iNrPliku);
        ifstream myfile ("SCHRAGE"+filename+".DAT");
        cout << "Odczytuje plik SZCHRAGE"+filename+".DAT\n";

        if (myfile.is_open()){
            myfile>>LiczbaZadan;
            for (unsigned int i = 0; i < LiczbaZadan; i++){
                myfile>>Zad.r;
                myfile>>Zad.p;
                myfile>>Zad.q;
                Zad.kolejnosc = i+1;
                //cout << Zad;
                WstawZadanie(Kolejka, Zad.kolejnosc, Zad.r, Zad.p, Zad.q);
            }
            myfile.close();
        }else cout << "Nie moge otworzyc pliku";
       
        // obsluga algorytmu, czyli petle zamieniajace kolejnosc dzialan
        cout<<"  Obliczanie kolejnosci. \n";
        //fdr(TabZadan, kolejnosc, LiczbaZadan);
        
        // wyswietlenie kolejnosci:
        cout << endl << "Wyliczona kolejnosc: ";
        WyswietlKolejke(Kolejka);
        int cm = cmax(Kolejka);
        
        cout << endl << "Czas Cmax: " << cm << endl;

        // zapis do pliku
        string fname = "out";
        fname.append(filename);
        fname.append(".txt");
        FILE *fp = fopen(fname.c_str(),"w");
        if (fp){
            fprintf(fp,"%d\n", cm);
            fclose(fp);
            cout << "Plik zostal zapisany.\n";
        }else {
            cout << "Nie moge otworzyc pliku " << filename << endl;
            return -1;
        }
        cout<<"###############################################\n\n";
    }
    showtime();
    return 0;
}