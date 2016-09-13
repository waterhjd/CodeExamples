#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <deque>
#include <queue> 

using namespace std;


typedef struct {
   deque<int> key;
   int val;
} keyVal;


class compare {
public: 
   bool operator() (keyVal i, keyVal j) {
      deque<int> key1 = i.key;
      deque<int> key2 = j.key;
      return (key1 > key2);
   }
};


int main(int argc, char* argv[]) {
   /*initialize random seed: */
   srand (time(NULL));
   
   // Make sure a single file name is specified
   if(argc != 2) {
      cout << "Invalid Parameter Set" << endl;
      return 0;
   }
   cout << "********************************" << endl;
   cout << "\nFilename: " << argv[1] << endl;
   char* fn = argv[1];
   
   vector<int> *Cover;
   fstream f;
   int v,u;
   int n = 0;
   int *Count;
   string linExt = "";
        
   f.open(fn);
   if (!f) {
      cerr << "File not openable. "<< endl; return 0;
      }
   f >> n;

   cout << "Number of vertices is: " << n << endl;

   
   if (n>100000) { cerr<<"n too large: "<<n<<endl; return 0;} // arbitrary

   Count = new int[n]();            // Array to keep track of covers   
   Cover = new vector<int>[n];  // all elements covering indexed elt 
   vector<int> linExtv; 
   int lexCount = 0;
   deque<int> lexProfile;
   deque<int>* vProfile  = new deque<int>[n];
   deque<int>* LexArr = new deque<int>[n]; 
   int* upperCount = new int[n];
   vector<int>* lowerCovers = new vector<int>[n];  

   f >> u;
   // Ripped out from Lab1 and added a count and vector pushback
   // this sets up out arrays for later 
   while (u<n && f) {
      f >> v;
      if(v < n)
      {
          Cover[u].push_back(v);
          lowerCovers[v].push_back(u);
          Count[v] += 1;
          upperCount[u]++;
      }
      while (v < n && f) {
         f >> v;
         if (v < n) {
            Cover[u].push_back(v);
            lowerCovers[v].push_back(u);
            Count[v] += 1;
            upperCount[u]++;
         }
      }
      f >> u;
   }
   f.close();

   keyVal vertex;

   priority_queue<keyVal, std::vector<keyVal>, compare> H;
   
   //Timing
   clock_t start;
   start = clock();
   
   // NEW STUFF
   for (int i = 0; i < n; i++) {
      if(upperCount[i] == 0)
      {
         LexArr[i] = deque<int>{0};
         linExtv.push_back(lexCount);
         linExtv.push_back(i);

         while(lowerCovers[i].size() > 0)
         {
            vProfile[lowerCovers[i].back()].push_front(lexCount);
            --upperCount[lowerCovers[i].back()];
            if(upperCount[lowerCovers[i].back()] == 0)
            {
               // Insert element withh key of 0
               
               vertex.key = vProfile[lowerCovers[i].back()];
               vertex.val = lowerCovers[i].back();
               
               cout << vertex.val << endl;
               H.push(vertex);

            }
            lowerCovers[i].pop_back();
         }
      }
   }

  while(!H.empty())
  {
   // H.top() is the min element on the heap the heap sorts lexographically
   // H.topKey is the lexographic profile of the top element
   if (lexProfile != H.top().key)
   {
      //cout << "Lex Profile: " << lexProfile.front();
      //if(lexProfile.size() > 1)
      //    cout << lexProfile.back();
      //cout << endl;
      //cout << "Top Key: " << H.top().key.front();
      //if (H.top().key.size() > 1)
      //    cout << H.top().key.back();
      //cout << endl;
      //cout << "LexCount: " << lexCount << endl;
      lexCount++;
   }

   //When the element is at the top of the heap assign it a lex number
   //LexArr[H.top().key] = lexCount;
   
   // Go through all of the lower covers assigning lex profile
   // If the vertex has no more upper covers insert it in to the heap
   while(lowerCovers[H.top().val].size() > 0)
   {
      vProfile[lowerCovers[H.top().val].back()].push_front(lexCount);
      --upperCount[lowerCovers[H.top().val].back()];
      
      if(upperCount[lowerCovers[H.top().val].back()] == 0) {
         
         vertex.key = vProfile[lowerCovers[H.top().val].back()];
         vertex.val = lowerCovers[H.top().val].back();

         H.push(vertex);
      }
      
      if (lowerCovers[H.top().val].size() > 0)
      lowerCovers[H.top().val].pop_back();
   }

   linExtv.push_back(lexCount);
   linExtv.push_back(H.top().val);
   lexProfile = H.top().key;
   //cout << "Top: " << H.top().val << endl;
   //cout << "Lex Profile: ";
   //for (int i = 0; i < H.top().key.size(); i++)
   //   cout << H.top().key.at(i);
   //   cout << endl;
   //remove top element from the heap
   H.pop();
  }
     
   cout << "\nThe linear extension is: " << endl;
   for (int i = 0; i < (2*n); i++)
   {

      if(i%2 != 0) 
         cout << "(";
      cout << linExtv.back(); 
      if(i%2 != 0)
         cout << ')';
      cout << " ";  
      linExtv.pop_back();
   }
   cout << "\n" << endl;
   cout << "Time: "<<(clock()-start)/(double(CLOCKS_PER_SEC/1000))<< endl;
   cout << "********************************" << endl;
   
   return 0;
}

