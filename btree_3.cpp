#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <conio.h> //clrscr

using std::cout;
using std::cin;
using std::endl;



// структура для данных
const int StrSize = 32;
struct STR {
	char S[ StrSize ];
};

// структура элемента
struct NODE {
	NODE* Parent;
	NODE* Child1;
	NODE* Child2;
	int Id;
	int Level;
	STR Data;
};

// структура дерево
struct BTREE {
	NODE* Root;
	NODE* Current;
	int Levels;
	int Count;
};

// структура айди - адрес узла - для восстановления дерева используется
struct ADDR {
	int IdPar;
	NODE* Parent;
};

void Help();

void AddNode (BTREE &Oak);

void AddData(STR &Data);
void PrintSummary( BTREE &Oak);
void ChangeNode(BTREE &Oak);
void PrintNode( BTREE &Oak);
void SaveToFile(BTREE &Oak);
void PrintThumbNode(NODE* Temp);
void PrintTree(BTREE &Oak);
void PrintToFileThumbNode(FILE* f, NODE* Temp);

void LoadFromFile(BTREE &Oak);
void DeleteTree(BTREE &Oak);
void DeleteBranch(NODE* &Temp);

void PrintNodeLikeTree(NODE* Temp);
void PrintTreeLikeTree(BTREE &Oak);

	//сажаем дерево
	BTREE Oak = {nullptr, nullptr, 0, 0};
	
	int IdCounter = 0;

  // для печати в виде дерева
    char Branch[] = "+---";
	char Stripe[] = "|   ";
	char Space[] = "    ";
	
	int* NeedStripe = nullptr;
	
	
int main(){

   char Sample[500] = "Evgen\n"
"+---Kate\n"
"|   +---Alex\n"
"|   |   +---Ilidze\n"
"|   |   +---Kirilidze\n"
"|   +---Nina\n"
"|       +---Polina\n"
"+---Fred\n"
"|   +---Anjela\n"
"|   +---Mike\n"
"|   +---Ada\n"
"|   +---Rita\n"
"+---Pamela\n";

 // cout << Sample;
 
    Help();
   bool WaitCom = true;
 
    while (true){
    	char Temp[ 256 ];
    	cout <<">";
    	cin >> Temp;
    	
    	if (WaitCom && strcmp(Temp, "help") == 0){
    		Help();
    		WaitCom = false;
    	}
    	if (WaitCom && strcmp(Temp, "new") == 0){
    		AddNode (Oak);
    		WaitCom = false;
    	}
    	if (WaitCom && strcmp(Temp, "ch") == 0){
    		ChangeNode(Oak);
    		WaitCom = false;
    	}
    	if (WaitCom && strcmp(Temp, "pr") == 0){
    		PrintNode(Oak);
    		WaitCom = false;
    	}
    	    	if (WaitCom && strcmp(Temp, "pr-s") == 0){
    		PrintSummary(Oak);
    		WaitCom = false;
    	}
    	   	    	if (WaitCom && strcmp(Temp, "pr-t") == 0){
    		PrintTree(Oak);
    		WaitCom = false;
    	}
    	   	    	if (WaitCom && strcmp(Temp, "tree") == 0){
    		PrintTreeLikeTree(Oak);

    		WaitCom = false;
    	}
    	        if (WaitCom && strcmp(Temp, "save") == 0){
    		SaveToFile(Oak);
    		WaitCom = false;
    	}
            if (WaitCom && strcmp(Temp, "load") == 0){
    		LoadFromFile(Oak);
    		WaitCom = false;
    	}
    	       if (WaitCom && strcmp(Temp, "del") == 0){
    		DeleteTree(Oak);
    		WaitCom = false;
    	}
    	    	if (WaitCom && strcmp(Temp, "cls") == 0){
    		//clrscr();
					system("pause");
    		WaitCom = false;
    	}
   	if (WaitCom && strcmp(Temp, "exit") == 0){
    		break;
    	}
    	if (WaitCom){
    		cout << "Wrong command\n";
    	}
    /*	if (!WaitCom){
    		cout << "Comand done!\n\n";
    	}
    	*/
    	WaitCom = true;
    }
	
	
	return 0;
}
// удаление дерева 
void DeleteTree(BTREE &Oak){
	
	if (Oak.Root){
	     DeleteBranch(Oak.Root);
	     Oak.Current = Oak.Root;
	     Oak.Levels = 0;
	     cout << "Tree deleted\n";
	}
	else {
		cout<<"Tree is absent\n";
	}
}
// удаление ветки
void DeleteBranch(NODE* &Temp){

	if (Temp){
		
			// рекурсивно удаляем детей
	   	if (Temp->Child1) DeleteBranch(Temp->Child1);
			if (Temp->Child2) DeleteBranch(Temp->Child2);
	// условие выхода: отсутствие детей	
	   // теперь удаляем себя
	  delete Temp;
	  Temp = nullptr;
	  Oak.Count--;
	  
	}
	else {
		cout << "Delete error\n";
	}
}


// печать дерева  в виде дерева
void PrintTreeLikeTree(BTREE &Oak){
	
	// вспомог. массив Последний ребя на уровне
	// 0,1 - элементы не исп.
	// 0 - реб. последний => полоска не нужна
	// 1 - реб. не последний => полоска нужна
	NeedStripe = new int [ Oak.Levels];
	
	
			printf("Count = %d\nLevels = %d\n", Oak.Count, Oak.Levels );
			
	if (Oak.Root){
	PrintNodeLikeTree(Oak.Root );
	}
	else {
		cout<<"Plant the tree!\n";
	}
	
	//delete[] NeedStripe;
	//NeedStripe = nullptr;
}

// печать узла в виде дерева
void PrintNodeLikeTree(NODE* Temp ){

	if (Temp){
	// установка параметров Stripe
	if (Temp->Child2){
		NeedStripe[Temp->Level +1] = 1;
	}
	else 
	NeedStripe[Temp->Level +1] = 0;
	
	// вывод ветки
	for (int i = 2 ; i  < Temp->Level ; i++){
		if (NeedStripe[i] == 1) printf("%s", Stripe);
		else printf("%s", Space);
	}
	if (Temp != Oak.Root) printf("%s", Branch);
	printf( "%s\n", Temp->Data.S );	
			// рекурсивно напечатаем детей
	   	if (Temp->Child1){ PrintNodeLikeTree(Temp->Child1);
	   	}
	   	//сброс флага полоски 	
	NeedStripe[Temp->Level +1] = 0;
	
			if (Temp->Child2){
	 PrintNodeLikeTree(Temp->Child2);
			}
	// условие выхода: отсутствие детей	
	}
	else {
		cout << "Print error\n";
	}
}

// печать дерева 
void PrintTree(BTREE &Oak){
	
			printf("Count = %d\nLevels = %d\n", Oak.Count, Oak.Levels );
		printf( "Id Level Name          Parent_id\n");
		
	if (Oak.Root){
	PrintThumbNode(Oak.Root);
	}
	else {
		cout<<"Plant the tree!\n";
	}
}

// печать узла краткая
void PrintThumbNode(NODE* Temp){
	// адрес родича
	int IdPar = 0; 
	
	if (Temp){
			NODE* PrCur = Temp;
			// считываем инфу о родиче: (если не корень)
			 if (Temp != Oak.Root ) IdPar = PrCur->Parent->Id;
					
	printf( "%-2d %-6d%-14s%-7d\n", 
			PrCur->Id, PrCur->Level, PrCur->Data.S, IdPar );	
			// рекурсивно напечатаем детей
	   	if (PrCur->Child1) PrintThumbNode(PrCur->Child1);
			if (PrCur->Child2) PrintThumbNode(PrCur->Child2);
	// условие выхода: отсутствие детей	
	}
	else {
		cout << "Print error\n";
	}
}

// печать в файл узла краткая
void PrintToFileThumbNode(FILE* f, NODE* Temp){
	// адрес родича
	int IdPar = 0;
	
	if (Temp){
			NODE* PrCur = Temp;
		// считываем инфу о родиче: (если не корень)
			 if (Temp != Oak.Root ) IdPar = PrCur->Parent->Id;
	fprintf(f, "%-2d %-6d%-14s%-7d\n", 
			PrCur->Id, PrCur->Level, PrCur->Data.S, IdPar);	
			// рекурсивно напечатаем детей
	   	if (PrCur->Child1) PrintToFileThumbNode(f, PrCur->Child1);
			if (PrCur->Child2) PrintToFileThumbNode(f, PrCur->Child2);
	// условие выхода: отсутствие детей	
	}
	else {
		cout << "Print error\n";
	}
}


//сохранить дерево в файл
void SaveToFile(BTREE &Oak){

		
	FILE* f = fopen("btree.txt", "w");
	if (f){
	
		fprintf(f, "Count = %d\nLevels = %d\n", Oak.Count, Oak.Levels );
		fprintf(f, "Id Level Name          Parent_id\n");
		
		if (Oak.Root){
	PrintToFileThumbNode(f, Oak.Root);
	}
	else {
		cout<<"Plant the tree!\n";
	}
	
		fclose(f);
		cout << "Saved in 'btree.txt'\n";
	}
	else {
		cout << "Cannot open file\n";
	}
}

//загрузить дерево из файла
void LoadFromFile(BTREE &Oak){
  int Choice = 0;
   printf("Loading will erase current tree. Continue?\n(1) YES (0) NO\n");
    printf(">");
    cin >> Choice;
    if (Choice == 1){
    	
    DeleteTree(Oak); // очищаемся
    
	FILE* f = fopen("btree.txt", "r");
	if (f){
	
		fscanf(f, "Count = %d\nLevels = %d\n", &Oak.Count, &Oak.Levels );
		fscanf(f, "Id Level Name          Parent_id\n");

	     // создание вспомогательной адресной табл. (int idPar, NODE* Parent)
ADDR* AdrPar = new ADDR[Oak.Count];
int Ptr = 0;	  // кол-во записей
      // кеш   
      int CIdPar = 0;
      NODE* CParent = nullptr;
		
		// считываем строки
		int IdPar = 0;
		for (int i = 0; i < Oak.Count; i++){	
			NODE* Temp = new NODE;
	    	fscanf(f, "%d %d %s %d\n", 
			&Temp->Id, &Temp->Level, Temp->Data.S, &IdPar);	
			// обновляем id счетчик 
     IdCounter = Temp->Id; 
	       // если корень
	       if (IdPar == 0){
	       	Oak.Root = Temp;
	       	Temp->Parent = nullptr;
	       	Temp->Child1 = nullptr;
	       	Temp->Child2 = nullptr;
	  	     printf("id %d loaded\n", Temp->Id);
  // вносим инфу в адресную табл.
  AdrPar[Ptr].IdPar = Temp->Id;
  AdrPar[Ptr].Parent = Temp;
	  	     Ptr++;
	  // сохраним инфу в кеш
	  CIdPar = Temp->Id;
	  CParent = Temp;
	  
	       }
	       // если не корень
	       else {
	 	// надо найти родителя
	 	// смотрим кеш сначала
	       	if (IdPar == CIdPar ){
	       	Temp->Parent = CParent;
	       	}
	// если нет попадания в кеш
	       	else {
	       		// бежим по адресной таблице в поисках id родича
	       		for (int i = 0; i < Ptr; i++){
	       			if (IdPar == AdrPar[i].IdPar){
	       				Temp->Parent = AdrPar[i].Parent;
	       				break;
	       				 } 
	       		}	
	       	}
	       	// привязываем родителя к ребенку
	       	// если нет детей, будет 1м
	       	if (!Temp->Parent->Child1) Temp->Parent->Child1 = Temp;
	       	// иначе будет 2м
	       	else Temp->Parent->Child2 = Temp;
	       	
	       	
	       	Temp->Child1 = nullptr;
	       	Temp->Child2 = nullptr;
	  	     printf("id %d loaded\n", Temp->Id);       	
	  	     
	  	      // вносим инфу в адресную табл.
  AdrPar[Ptr].IdPar = Temp->Id;
  AdrPar[Ptr].Parent = Temp;
	  	     Ptr++;
	  // сохраним инфу в кеш
	  CIdPar = Temp->Id;
	  CParent = Temp;
	       }
		} // конец чтения строк
		
		fclose(f);
		Oak.Current = Oak.Root;
		delete[] AdrPar;
		AdrPar = nullptr;
	cout << "Tree loaded from 'btree.txt'\n";
	}
	else {
		cout << "Cannot open file\n";
	}
    }
    else{
    	cout << "Loading canceled\n";
    }

}

// печать меню
void Help(){
	printf("--------------------------------------------\n");
	printf("              ^^ Binary tree ^^\n");
	printf("--------------------------------------------\n");
	printf("Commands:\n");
	printf("help\tPrint info page\n");
	printf("new\tCreate child node\n");
	printf("ch\tChange current node\n");
	printf("pr\tPrint current node\n");
	printf("pr-s\tPrint tree summary\n");
	printf("pr-t\tPrint whole tree\n");
	printf("tree\tPrint tree like tree\n");
	printf("save\tSave tree to file\n");
	printf("load\tLoad tree from file\n");
	printf("del\tDelete tree\n");
	printf("cls\tClear screen\n");
	printf("exit\tExit program\n");
	printf("--------------------------------------------\n");
}
//печать текущего элемента
void PrintNode( BTREE &Oak){
	if (Oak.Current){
  	printf("Name Id Level\n%s %d %d\n", Oak.Current->Data.S, Oak.Current->Id, Oak.Current->Level );
  	// printf("Childrens:\n");
  	if (Oak.Current->Child1) printf("+---%s %d %d\n",  Oak.Current->Child1->Data.S, Oak.Current->Child1->Id, Oak.Current->Child1->Level );
  	if (Oak.Current->Child2) printf("+---%s %d %d\n",  Oak.Current->Child2->Data.S, Oak.Current->Child2->Id, Oak.Current->Child2->Level );
  		if (!Oak.Current->Child1 && !Oak.Current->Child2) cout << "No children\n";
	}
	
	else{
		cout << "No tree yet\n";
	}
}
//печать информации о дереве
void PrintSummary( BTREE &Oak){
  if (Oak.Root) {
  	printf("Root: %s\n", Oak.Root->Data.S);
  	printf("Current: %s\n", Oak.Current->Data.S);
  }
  else cout <<"No root\n";
  
  printf("Node count: %d\n", Oak.Count);
   printf("Node levels: %d\n", Oak.Levels);
}

//добавить элемент
void AddNode(BTREE &Oak){
	    NODE* Temp = nullptr;
	        // если корня нет
			if (!Oak.Root ){  
			Temp = new NODE;
			Oak.Root = Temp;
			Oak.Current = Temp;
			Temp->Parent = nullptr;
			Temp->Child1 = nullptr;
			Temp->Child2 = nullptr;
			Temp->Level = 1; // корень же
			printf("Root:\n>");
		}
		//если нет 1 ребенка
		else if (!Oak.Current->Child1 ){
	   	Temp = new NODE;
	   	Oak.Current->Child1 = Temp;
			Temp->Parent = Oak.Current;
			Temp->Child1 = nullptr;
			Temp->Child2 = nullptr;	
			Temp->Level = Oak.Current->Level + 1;
			printf("%s's 1st child:\n>", Oak.Current->Data.S );
		}
		//если есть только 1 ребенок
		else if (!Oak.Current->Child2 ){
	   	Temp = new NODE;
	   	Oak.Current->Child2 = Temp;
			Temp->Parent = Oak.Current;
			Temp->Child1 = nullptr;
			Temp->Child2 = nullptr;	
			Temp->Level = Oak.Current->Level + 1;
			printf("%s's 2nd child:\n>", Oak.Current->Data.S );
		}
		// если уже 2 детей
		else if (Oak.Current->Child1 && Oak.Current->Child1){
			cout << Oak.Current->Data.S << " have already 2 childrens!\nYou can use command 'ch' to change node\n";
			return;
		}
		else {
			cout << "Error\n";
		}
		// добавляем данные в узел
		AddData(Temp->Data); 
		// присваиваем идентификатор узлу
		Temp->Id = ++IdCounter; 
// увеличиваем общий счетчик узлов
		Oak.Count++;  
		// обновляем инфу о уровнях
		if (Temp->Level > Oak.Levels) Oak.Levels = Temp->Level;
	
}

//добавление данных в элемент

void AddData(STR &Data){
	cin >>Data.S;
	printf("%s created\n", Data.S);
}

// сменить текущий элемент
void ChangeNode(BTREE &Oak){
	int Direct;
	printf("(-2) ROOT (-1) PARENT (0) CHILD1 (1) CHILD2\n");
	printf(">");
	scanf("%d", &Direct);
	switch(Direct){
		case -2:
		Oak.Current = Oak.Root;
		break;
		
		case -1:
		if (Oak.Current->Parent){ //есть родич
		Oak.Current = Oak.Current->Parent;
		}
		else { //корневой уже
		cout << "Current is root!\n";
		}
		break;
		
		case 0:
				if (Oak.Current->Child1){ //есть 1 ребя
		Oak.Current = Oak.Current->Child1;
		}
		else { // все таки нет 1 реби
		cout << "Child_1 is absent!\n";
		}
		break;
		
		case 1:
	    	if (Oak.Current->Child2){ //есть 2й ребя
		Oak.Current = Oak.Current->Child2;
		}
		else { // все таки нет 2 реби
		cout << "Child_2 is absent!\n";
		}
		break;
		default:
		cout << "Error direction!\n";
	}
	PrintNode(Oak);
}