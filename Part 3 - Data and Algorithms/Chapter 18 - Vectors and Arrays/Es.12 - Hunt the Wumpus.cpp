#include "std_lib_facilities.h"
constexpr int max_connections = 3;	//we declare a symbolic constant
enum class Hazard{NONE=0,BAT,PIT,WUMPUS};

class Room{
public:
	//default constructor and room number constructor
	Room(): room_num{0}, haz(Hazard::NONE) {}
	Room(int room_num);
	
	//private member return functions
	int room_number() const {return room_num;}
	Hazard hazard() const {return haz;}
	
	//modify members
	void link_rooms(vector<Room*> rooms, int link_1, int link_2, int link_3);
	void set_hazard(Hazard h) {haz=h;}
	
	//linked rooms
	vector<Room*> linked_rooms;//this vector can be public as it holds pointers. If there was a function to return the vector to modify it, there would be no difference
	bool in_linked_room(Hazard haz) const;
	bool is_linked_to(Room* room) const;
private:
	int room_num;
	Hazard haz;
	
};

Room::Room(int room_num)
	: room_num{room_num}, haz{Hazard::NONE}
{
	if(room_num<1) error("Non positive room number");
}

void Room::link_rooms(vector<Room*> rooms, int link_1, int link_2, int link_3)
{
	linked_rooms.push_back(rooms[link_1-1]);
	linked_rooms.push_back(rooms[link_2-1]);
	linked_rooms.push_back(rooms[link_3-1]);
}

bool Room::in_linked_room(Hazard haz) const
{
	for(Room* lr : linked_rooms)
	{
		if(lr->hazard() == haz) return true;
	}
	
	return false;
}

bool Room::is_linked_to(Room* room) const
{
	for(Room* lr : linked_rooms)
	{
		if(room == lr) return true;
	}
	return false;
}

struct Cave{
	Cave();
	
	int number_of_rooms() const {return num_of_rooms;}
	vector<Room*> rooms;
	void wake_wumpus();
private:
	int num_of_rooms;
	int bats_num;
	int pits_num;
	int wumpus_num;
	void place_hazard(Hazard haz, int rooms_to_fill);
};

void Cave::place_hazard(Hazard haz, int rooms_to_fill)
{
	srand(time(NULL));
	for(int i=0;i<rooms_to_fill;++i)
	{
		while(true)
		{
			int room_index = rand()%num_of_rooms; //0 to num_of_rooms - 1
			if(rooms[room_index]->hazard() != Hazard::NONE) continue;
			
			int haz_count {0};
			
			/*
			for(int i=0;i<max_connections;++i)
			{
				if(rooms[room_index]->linked_rooms[i]->hazard() != Hazard::NONE)
					haz_count++;
			}
			*/
			
			for(Room* lr : rooms[room_index]->linked_rooms)
			{
				if(lr->hazard() != Hazard::NONE)
					haz_count++;
			}
			
			if(haz_count>1) continue;
			
			rooms[room_index]->set_hazard(haz);
			break;
		}
	}
}

Cave::Cave() : num_of_rooms{20}, bats_num{4}, pits_num{4}, wumpus_num{1}
{
	//initialize room with their number first
	for(int i=0;i<num_of_rooms;++i)
	{
		rooms.push_back(new Room{i+1});	//we allocate the rooms on the free store. Had we not done this, upon exiting the loop there would have been a memory leak
	}
	
	rooms[0]->link_rooms(rooms,2,5,8);
	rooms[1]->link_rooms(rooms,1,3,10);
	rooms[2]->link_rooms(rooms,2,4,12);
	rooms[3]->link_rooms(rooms,3,5,14);
	rooms[4]->link_rooms(rooms,1,4,6);
	rooms[5]->link_rooms(rooms,5,7,15);
	rooms[6]->link_rooms(rooms,6,8,17);
	rooms[7]->link_rooms(rooms,1,7,9);
	rooms[8]->link_rooms(rooms,8,10,18);
	rooms[9]->link_rooms(rooms,2,9,11);
	rooms[10]->link_rooms(rooms,10,12,19);
	rooms[11]->link_rooms(rooms,3,11,13);
	rooms[12]->link_rooms(rooms,12,14,20);
	rooms[13]->link_rooms(rooms,4,13,15);
	rooms[14]->link_rooms(rooms,6,14,16);
	rooms[15]->link_rooms(rooms,15,17,20);
	rooms[16]->link_rooms(rooms,7,16,18);
	rooms[17]->link_rooms(rooms,9,17,19);
	rooms[18]->link_rooms(rooms,11,18,20);
	rooms[19]->link_rooms(rooms,13,16,19);
	
	place_hazard(Hazard::BAT,bats_num);
	place_hazard(Hazard::PIT,pits_num);
	place_hazard(Hazard::WUMPUS,wumpus_num);
}

void Cave::wake_wumpus()
{
	Room* wump_room;
	for(Room* lr : rooms)
	{
		if(lr->hazard() == Hazard::WUMPUS)
		{
			wump_room = lr;
			break;
		}
	}
	
	while(true)
	{
		int rand_room_index = rand()%3;
		if(wump_room->linked_rooms[rand_room_index]->hazard() != Hazard::NONE)
			continue;
		
		wump_room->set_hazard(Hazard::NONE);
		wump_room->linked_rooms[rand_room_index]->set_hazard(Hazard::WUMPUS);
		break;
	}
}

struct Player{
	Player(): current_room{nullptr}, arrows_left{5} {}
	Room* current_room;
	int arrows_left;
};

void setup_player_room(Player& player, Cave& cave)
{
	srand(time(NULL));
	
	while(true)
	{
		int start_room_index = rand()%cave.number_of_rooms();
		if(cave.rooms[start_room_index]->hazard() != Hazard::NONE) continue;
		
		player.current_room = cave.rooms[start_room_index];
		break;
	}
}

void debug_output(Player& player, Cave& cave)
{
	for(int i=0;i<cave.number_of_rooms();++i)
	{
		cout << i+1 <<": ";
		
		for(int j=0;j<max_connections;++j)
		{
			cout << cave.rooms[i]->linked_rooms[j]->room_number();
			if(j<2) cout << ", ";
			else cout << ". ";
		}
		
		cout << "Hazard: ";
		switch(cave.rooms[i]->hazard())
		{
			case Hazard::NONE:
				cout << "None";
				break;
			case Hazard::BAT:
				cout << "Bat";
				break;
			case Hazard::PIT:
				cout << "Pit";
				break;
			case Hazard::WUMPUS:
				cout << "WUMPUS";
				break;
		}
		cout << '\n';
	}
	
}

void report_status(Player& player)
{
	cout << '\n';
	if(player.current_room->in_linked_room(Hazard::BAT))
		cout << "I hear a bat\n";	
	if(player.current_room->in_linked_room(Hazard::PIT))
		cout << "I feel a breeze\n";
	if(player.current_room->in_linked_room(Hazard::WUMPUS))
		cout << "I smell the Wumpus\n";
		
	cout << "You are in room " << player.current_room->room_number()
			<< "; tunnels lead to rooms ";
			
	for(int i=0;i<max_connections;++i)
	{
		cout << player.current_room->linked_rooms[i]->room_number();
		if(i<2) cout << ", ";
	}
	cout << "; (m)ove or (s)hoot?\n";
}

enum class Game_state {START = 0, RUNNING, LOST, WON};

void handle_state(Game_state& game)
{
	if(game == Game_state::LOST || game == Game_state::WON)
	{
		if(game == Game_state::LOST)
		{
			cout << "You have lost!\n";
			
		}
		else if(game == Game_state::WON)
		{
			cout << "You killed the Wumpus! You have won!\n";
		}
		
		while(true)
		{
			char ch;
			cout << "Try again? Y/N: ";
			cin>>ch;
			
			if(ch=='Y')
			{
				game = Game_state::START;
				break;
			}
			else if(ch=='N')
				break;
			else
				cout << "Invalid answer!\n";
		}
	}
}

void flush_buffer(istream& is)
{
	string a;
	getline(is,a);	
}

int main()
try
{
	Game_state game = Game_state::START;
	
	while(game == Game_state::START)
	{
		Cave wumpus_cave;
		Player player;
		setup_player_room(player,wumpus_cave);
		
		game = Game_state::RUNNING;
		//debug_output(player,wumpus_cave);
		system("cls");
		while(game == Game_state::RUNNING)
		{
			//system("cls");
			report_status(player);
			
			bool bad_input{false};
			char action;
			cin>>action;
			if(action == 'm')
			{
				int next_room;
				cin>>next_room;
				
				if(next_room < 1 || 20 < next_room)
				{
					cout << "Room " << next_room << " is out of range; try again.\n";
					flush_buffer(cin);
				}
				else if(player.current_room->is_linked_to(wumpus_cave.rooms[next_room-1]))
				{
					player.current_room = wumpus_cave.rooms[next_room-1];
				}
				else
				{
					cout<<"Room " << next_room << " is not connected; try again.\n";
					flush_buffer(cin);
				}
					
			}
			else if(action == 's')
			{
				string init_ss;
				cin>>init_ss;
				stringstream ss{init_ss};
				vector<Room*> rooms_shot;
				
				for(int selected_room_num; ss>>selected_room_num;)
				{
					if(selected_room_num <1 || selected_room_num >20)
					{
						cout << "Room out of range; try again.\n";
						flush_buffer(ss);
						break;
					}
					
					if(player.current_room->is_linked_to(wumpus_cave.rooms[selected_room_num-1]))
					{
						rooms_shot.push_back(wumpus_cave.rooms[selected_room_num-1]);
						char separator;
						if(ss>>separator && separator != '-')
						{
							bad_input = true;
							break;
						}
					}
					else
					{
						cout << "Room " << selected_room_num << " is not connected; try again.\n";
						flush_buffer(ss);
						bad_input = true;
						break;
					}
					
					if(rooms_shot.size()>max_connections)
					{
						bad_input = true;
						break;
					}
					
				}
				
				for(int i=0;i<rooms_shot.size();++i)
				{
					for(int j=0;j<rooms_shot.size();++j)
					{
						if(rooms_shot[i] == rooms_shot[j] && i!=j)
						{
							bad_input=true;
							break;
						}
					}
				}
				
				bool wumpus_nearby{false};
				
				if(!bad_input)
				{
					player.arrows_left-=rooms_shot.size();
					if(player.arrows_left<=0)
					{
						cout << "You have run out of arrows! ";
						game = Game_state::LOST;
					}
					
					if(game != Game_state::LOST)
					{
						for(Room* lr : player.current_room->linked_rooms)
						{
							if(lr->hazard() == Hazard::WUMPUS)
							{
								for(Room* rs : rooms_shot)
								{
									if(rs == lr)
									{
										game = Game_state::WON;
										break;
									}
								}
								if(game != Game_state::WON)
								{
									wumpus_nearby=true;
									break;
								}
							}
							
							if(game == Game_state::WON)
								break;
						}
					}
					
					if(game != Game_state::WON && wumpus_nearby)
					{
						srand(time(NULL));
						int extract = rand()%4;
						if(extract != 0)
						{
							wumpus_cave.wake_wumpus();
							cout << "The Wumpus has changed room!\n";
						}
					}
				}
			}
			if(bad_input)
			{
				cout << "Invalid action; try again.\n";
				flush_buffer(cin);
				continue;
			}
			
			switch(player.current_room->hazard())
			{
				case Hazard::PIT:
					cout << "You fell into a bottomless pit! ";
					game = Game_state::LOST;
					break;
				case Hazard::WUMPUS:
					cout << "You have been eaten by the Wumpus! ";
					game = Game_state::LOST;
					break;
				case Hazard::BAT:
				{
					while(true)
					{
						int new_room_index=rand()%wumpus_cave.number_of_rooms();
						if(wumpus_cave.rooms[new_room_index]->hazard() == Hazard::NONE && new_room_index!=player.current_room->room_number()-1)
						{
							player.current_room=wumpus_cave.rooms[new_room_index];
							cout << "You have been transported to another room!\n";
							break;
						}
					}
					break;
				}
			}
			handle_state(game);
		}
	}
	return 0;
}

catch(exception& e)
{
	cerr<<"error:"<<e.what()<<'\n';
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"Unknown error"<<'\n';
	keep_window_open();
	return 2;
}
