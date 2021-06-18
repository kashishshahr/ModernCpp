#include<string>
#include<algorithm>
#include<iostream>
#include<memory>
#include<vector>
#include<ranges>

using namespace std;
namespace ranges = std::ranges;

class MediaAsset
{
public:
	virtual ~MediaAsset() = default;
};


class Song :public MediaAsset
{
public:
	string artist, title;
	Song(const string& a, const string& t) :artist{ a }, title{ t }{}
};


class Photo :public MediaAsset
{
public:
	string data, location, subject;
	Photo(const string& date_,
		  const string& location_,
		  const string& subject_):data{date_},location{location_},subject{subject_}{}
		
};


void Example1()
{
	//Use Make Shared when possible
	auto sp1 = std::make_shared<Song>("The Beatles", "I'm Happy...");



	//Separate blocks
	//slightly less efficient but useful in some scenarios
	shared_ptr<Song> sp2{ new Song("Lady Gaga","Just Dance") };



	//if instance cant be initialized set to nullptr;
	shared_ptr<Song> sp3{ nullptr };

	//...

	sp3 = make_shared<Song>("Elton John", "I'm still standing");

	
	auto sp4(sp3);//initializer with cctor
	//sp4=sp3=same object
}


void Example2()
{
	vector<shared_ptr<Song>> vsp1{
		make_shared<Song>("Bob Dylan","The Times they are a Changing"),
		make_shared<Song>("Aretha Franklin","Bridge over the Troubled water"),
		make_shared<Song>("Thalia","Entre El Mar y Una Estrella")
	};
	//vector of shared pointers


	vector<shared_ptr<Song>> vsp2;
	//remove while copying if...BOB dylan ...will not get copied 
	remove_copy_if(vsp1.begin(), vsp1.end(), back_inserter(vsp2), [](shared_ptr<Song> song) {
		return song->artist.compare("Bob Dylan") != 0;
		});
	/*copy_if(vsp1.begin(), vsp1.end(), back_inserter(vsp2), [](shared_ptr<Song> song) {
		return song->artist.compare("Bob Dylan") != 0;
		});*/

	for(const auto& s:vsp2)
	{
		cout << s->artist << " : " << s->title << endl;
	}

}
void Example3()
{
	vector<shared_ptr<MediaAsset>> vsp1{
		make_shared<Song>("Bob Dylan","The Times they are a Changing"),
		make_shared<Photo>("DAIICT","Neem tree near lab","Neem"),
		make_shared<Song>("Aretha Franklin","Bridge over the Troubled water"),
		make_shared<Song>("Thalia","Entre El Mar y Una Estrella"),
		make_shared<Photo>("DAIICT","Lotus Pond roundabout","Lotus")
	};
	/*vector<shared_ptr<MediaAsset>> vphoto_sp;
	copy_if(vsp1.begin(), vsp1.end(), back_inserter(vphoto_sp), [](shared_ptr<MediaAsset> media) {
		auto ptr = dynamic_pointer_cast<shared_ptr<Photo>>(media);
		return ptr.get() != nullptr;
		});
	for_each(vphoto_sp.begin(), vphoto_sp.end(), [](shared_ptr<MediaAsset> photo) {
		auto ptr = dynamic_pointer_cast<shared_ptr<Photo>>(photo);
		
		});*/
	
	
}
void sharedPtr()
{
	Example1();
	Example2();
	Example3();
}
void main()
{
	sharedPtr();
}
