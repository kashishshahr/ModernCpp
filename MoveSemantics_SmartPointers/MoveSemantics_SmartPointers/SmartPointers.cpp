#include <iostream>
#include <memory>
using namespace std;
//Smart Pointers:
//	unique_ptr
//	shared_ptr
//	weak_ptr
//they can point to anything 
//Main: When we point to an object ..ptr does two things:	
//										getting information back 
//										also who owns the object
//				   	     _
//						| |	
//    		    p ----->| |<----- q
//						|_|	
//						Free Store	
//So who will be responible for cleaning this object from free store
//
//Managed Java c sharp manage only memory 
//Smart pointer covers everything NOTHING special for non memory resources

//unique_ptr
//SINGLE ownership -> only one ptr points to an ob
// 
//Stack			|	FS						main()
//(int*)UPTR----|---->	| 20 | int					{{
//				|								unique_ptr<int> uptr =make_uniu<int>();
//				|								*uptr=20;	
//				|								cout<<*uptr;
//				|									}
//				|					dtor of uptr will be called after scope -> delete on int* inside of uptr
//				|								}
//				|
//				|
//				|
//				|
//				|
//
//	main()
// {
//	unique_ptr<int> p1=make_unique<int>();
//	*p=20;
// unique_ptr<int> p2=p1;//ERROR  ->cctor 
//	p2=p1//ERROR//-> =()
// }
//		one ptr at a time to a memloc
//
//
//class unique_ptr	
//{	
//	unique_ptr(unique_ptr&)=delete
//	operator=(unique_ptr&)=delete
//
//}


//void	fun(unique_ptr<int> p)
//{
//}
//
// 
// unique_ptr<int> p1=make_unique<int>();
//fun(p1)//EROORRRRR not allowed		
//
//
// fun(move(p1)); -> ownership tranfer  ..p1's ownership will be transferred to p in fun(p)
// 
// 
//
//----------------------------------------

//shared_ptr	
//	JOINT ownership,	reference counted
//		obj is deleted when reference counting is zero.
// 
//Stack			|	FS					
//  p1	----|	|
//	p2  ----|---|--> |50|					
//	p3  ----|	|						
//				|						
//				
//even after deleting p2 and p3 due to scope we still have that object with p1.
//so REFERENCE counted
//
// a control block is also created..p1 pointing to object so
//p1 points to actual object and also control block
//Share pointer is also a class STD template library class
//when DTOR is called...it will check ref count==0 then only delete
//
//
//main()
//{
//	shared_ptr<int> p1 = make_shared<int>(20);
//	p1 = make_shared<fstream>();
//	//close will be automatically called...just as delete in memory
//	//p1 = make_shared<fstream,fptr>();
//		fptr -> deletor which gives flexibility and deterministic delting
// 
//	shared_ptr<int> p2 = make_shared(p1);
//	shared_ptr<int> p3 = p1;		cctor
//	shared_ptr<int> p4'		
//	p4= = p1;		=()
// all will point to same object...and be deleted after scope ending 
// 
//}


// akways use make_shared() why> ?  -> ptr are used very heaavily and even a fraction of cost benefit can lead to large benefit
//  gain performance  -> big performance upgrade and vice versa


//-object block and control block so 2 new call internally takes more time ...bcz FS call is costly
// make_share is must to use to avoid above point
// it allocates same memory and bifurcates them into 2 blocks..single block bifurcated into two blocks
//thus whole thing will be destroyed together


// 
//Stack			|	FS					
//		when new is used
//  p1	----|	| new |> |50|					Object Block(value)
//	p2  ----|=========|
//	p3  ----|	| new |> | 3|						Control Block(ref count)
//				|		
// 
// 		when make_shared is used
//			|			   	Object Block(value)
//  p1	----|	new			__________________	
//	p2  ----|=========|>	|50				3|
//	p3  ----|				|________________|
//			|				Control Block(ref count)
//							
//				sometime are there when make shared not be used

//fun(p2)
// 
//void fun(sp<int>p4)
//{
//	p4
//}
//Little bit cost -> bcz of ref count....possible use Unique ptr

//

//Weak ptr
//		1) ptr that  Doesnt participate in reference counting
//		
// 		when make_shared is used

//	sp2  ---|=========|>	|50				1|  ref ount will remain one as it doesnot participate in REFCOUNT
// wp1   ---|======== ^
// 
//							
// wp1.lock() -> returns share pointer or nullptr
// 
// useful to break the cyclic references		
//main()
//{
//	shared_ptr sp = make_shared<int>(20);
//	weak_ptr p = sp;
//	p.lock();
//	p.swap();
//}

//
//		is there are two objects
//
//	1<-ref	sp1  <====> sp2 ref ->1
//	now this is cyclic ..so break cyclic ref ....in this case...to break we have two objects sp1,sp2
// so sp1 -> sp2(SP)
//	  sp2 -> sp1(WP)
//						No cyclic ref....with wp no ref count increases
// 
// Be AWAre in ->  in a graph..obj pointing to each other using SP....cyclic ref not allowed so use WP				
//in control block RefCount and WeakPointers count is also there  SP can destroy object block but it cant destroy control blck as long as WP is there   if RC=WP=0 then deletion of CB will happen
// 
// WP doesnt take ownership
//
//
//







