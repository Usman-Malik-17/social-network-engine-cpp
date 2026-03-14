#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Page;
class User;
class Controller;
class Post;
class Object;
class Comments;
class Activity;
class Date;
class Memory;
class Date
{
private:
    int day;
    int month;
    int year;

public:
    static int currDay;
    static int currMonth;
    static int currYear;
    static void SetCurrentDate(int d, int m, int y)
    {
        currDay = d;
        currMonth = m;
        currYear = y;
    }
    static void PrintCurrDate()
    {
        cout << "(" << currDay << "/" << currMonth << "/" << currYear << ")" << endl;
    }
    Date();
    void SetDay(int);
    void SetMonth(int);
    void SetYear(int);
    void PrintDate();
    int GetDay();
    int GetMonth();
    int GetYear();
    void SetDate(int, int, int);
};
Date::Date()
{
    day = 0;
    month = 0;
    year = 0;
}
// setters
void Date::SetDay(int day)
{
    this->day = day;
}
void Date::SetMonth(int month)
{
    this->month = month;
}
void Date::SetYear(int year)
{
    this->year = year;
}
void Date::SetDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}
void Date::PrintDate()
{
    cout << "(" << day << "/" << month << "/" << year << ")" << endl;
}
// getters
int Date::GetDay()
{
    return day;
}
int Date::GetMonth()
{
    return month;
}
int Date::GetYear()
{
    return year;
}
int Date::currDay = 0;
int Date::currMonth = 0;
int Date::currYear = 0;
class Activity
{
    char** activities;
    int type;
    char* value;

public:
    Activity();
    ~Activity();
    void SetValue(const char*);
    void SetType(int);
    char* GetActivity();
    char* GetValue();
};
Activity::Activity()
{
    activities = new char* [4];
    activities[0] = new char[strlen("is feeling") + 1];
    strcpy(activities[0], "is feeling");
    activities[1] = new char[strlen("is thinking about") + 1];
    strcpy(activities[1], "is thinking about");
    activities[2] = new char[strlen("is making") + 1];
    strcpy(activities[2], "is making");
    activities[3] = new char[strlen("is celebrating") + 1];
    strcpy(activities[3], "is celebrating");
    type = 0;
    value = 0;
}
Activity::~Activity()
{
    if (activities != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            delete[] activities[i];
        }
        delete[] activities;
    }
    if (value != nullptr)
    {
        delete[] value;
    }
}
void Activity::SetValue(const char* c)
{
    if (value == 0)
    {
        value = new char[strlen(c) + 1];
    }
    else
    {
        delete[] value;
        value = new char[strlen(c) + 1];
    }
    strcpy(value, c);
    value[strlen(c)] = '\0';
}
void Activity::SetType(int i)
{
    type = i;
}
char* Activity::GetActivity()
{
    return activities[type - 1];
}
char* Activity::GetValue()
{
    return value;
}
class Comments
{
private:
    char* commentID;
    Post* postID;
    Object* commentBy;
    char* comment;

public:
    Comments();
    ~Comments();
    // getters
    Object* GetCommentBy();
    char* GetComment();
    // setters
    void SetId(char*);
    void SetPostId(Post*);
    void SetCommentBy(Object*);
    void SetCommentDescription(char*);
};
Comments::Comments()
{
    commentID = nullptr;
    postID = nullptr;
    commentBy = nullptr;
    comment = nullptr;
}
Comments::~Comments()
{
    if (commentID != nullptr)
    {
        delete[] commentID;
    }
    if (comment != nullptr)
    {
        delete[] commentID;
    }
}
Object* Comments::GetCommentBy()
{
    return commentBy;
}
char* Comments::GetComment()
{
    return comment;
}
void Comments::SetId(char* buffer)
{
    if (commentID == nullptr)
    {
        commentID = new char[strlen(buffer) + 1];
    }
    strcpy(commentID, buffer);
    commentID[strlen(buffer)] = '\0';
}
void Comments::SetPostId(Post* p)
{
    postID = p;
}
void Comments::SetCommentBy(Object* o)
{
    commentBy = o;
}
void Comments::SetCommentDescription(char* buffer)
{
    if (comment == 0)
    {
        comment = new char[strlen(buffer) + 1];
    }
    strcpy(comment, buffer);
    comment[strlen(buffer)] = '\0';
}
class Object
{
private:
    char* dummy;

public:
    Object();
    virtual ~Object();
    virtual char* GetID();
    virtual void printInfo();
    virtual void AddToTimeline(Post*);
    virtual void PrintName();
};
Object::Object()
{
    dummy = new char[1];
    dummy[0] = '\0';
}
Object::~Object()
{
    if (dummy != nullptr)
    {
        delete[] dummy;
    }
}
char* Object::GetID()
{
    return dummy;
}
void Object::printInfo()
{
}
void Object::AddToTimeline(Post*)
{
}
void Object::PrintName()
{
}
class Post
{
private:
    char* ID;
    char* Title;
    Object* sharedBy;
    Object** likedBy;
    Comments** comments;
    Activity* activity;

public:
    Date* sharedDate;
    ~Post()
    {
        if (!ID)
        {
            delete[] ID;
        }
        if (!Title)
        {
            delete[] Title;
        }
        if (!likedBy)
        {
            delete[] likedBy;
        }
        if (!comments)
        {
            for (int i = 0; comments[i] != nullptr; i++)
            {
                delete[] comments[i];
            }
            delete[] comments;
        }
        if (!activity)
        {
            delete[] activity;
        }
    }
    void PrintComments()
    {
        if (comments == nullptr)
        {
            return;
        }
        for (int i = 0; comments[i] != nullptr; i++)
        {
            comments[i]->GetCommentBy()->PrintName();
            cout << ":\t" << comments[i]->GetComment() << endl;
        }
    }
    void PrintActivity()
    {
        if (activity == nullptr)
        {
            return;
        }
        cout << " " << activity->GetActivity() << activity->GetValue() << " ";
    }
    void SetActivity(Activity* a)
    {
        activity = a;
    }
    Post();
    void PrintPost();
    void AddComment(Comments*);
    void ReadDataFromFile(ifstream&);
    void AddSharedBy(Object*&);
    void AddLikedBy(Object*&);
    void PrintLikedBy();
    char* GetTitle();
    // getters
    char* GetID();
    Object* SharedBy();
    void PrintSharedDate();
    // setters
    void SetTitle(const char*);
};
Post::Post()
{
    activity = 0;
    ID = 0;
    Title = 0;
    sharedBy = 0;
    likedBy = 0;
    comments = 0;
    sharedDate = 0;
}
// Post::~Post()
// {
//     if (!ID)
//     {
//         delete[] ID;
//     }
//     if (!Title)

//     {
//         delete[] Title;
//     }
//     if (!likedBy)
//     {
//         delete[] likedBy;
//     }
//     if (!comments)
//     {
//         delete[] comments;
//     }
// }
void Post::SetTitle(const char* c)
{
    if (Title == 0)
    {
        Title = new char[strlen(c) + 1];
    }
    else
    {
        delete[] Title;
        Title = new char[strlen(c) + 1];
    }
    strcpy(Title, c);
    Title[strlen(c)] = '\0';
}
void Post::PrintSharedDate()
{
    if (sharedDate->GetDay() == Date::currDay && sharedDate->GetMonth() == Date::currMonth && sharedDate->GetYear() == Date::currYear)
    {
        cout << "(1h)" << endl;
    }
    else if (sharedDate->GetDay() == Date::currDay - 1 && sharedDate->GetMonth() == Date::currMonth && sharedDate->GetYear() == Date::currYear)
    {
        cout << "(1d)" << endl;
    }
    else if (sharedDate->GetDay() == Date::currDay - 2 && sharedDate->GetMonth() == Date::currMonth && sharedDate->GetYear() == Date::currYear)
    {
        cout << "(2d)" << endl;
    }
    else if (sharedDate->GetDay() == Date::currDay - 3 && sharedDate->GetMonth() == Date::currMonth && sharedDate->GetYear() == Date::currYear)
    {
        cout << "(3d)" << endl;
    }
    else
    {
        sharedDate->PrintDate();
    }
}
Object* Post::SharedBy()
{
    return sharedBy;
}
char* Post::GetID()
{
    return ID;
}
char* Post::GetTitle()
{
    return Title;
}
void Post::PrintLikedBy()
{
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Post liked by:" << endl;
    if (likedBy == 0)
    {
        cout << "This post has no likes." << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        return;
    }
    for (int i = 0; likedBy[i] != nullptr; i++)
    {
        likedBy[i]->printInfo();
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
void Post::AddLikedBy(Object*& o)
{
    if (likedBy == 0)
    {
        likedBy = new Object * [11];
        for (int i = 0; i < 11; i++)
        {
            likedBy[i] = nullptr;
        }
    }
    int i = 0;
    while (likedBy[i] != nullptr)
        i++;
    likedBy[i] = o;
}
void Post::AddSharedBy(Object*& o)
{
    sharedBy = o;
}
void Post::ReadDataFromFile(ifstream& fin)
{
    char buffer[100];
    fin >> buffer;
    if (ID == 0)
    {
        ID = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] ID;
        ID = new char[strlen(buffer) + 1];
    }
    strcpy(ID, buffer);
    ID[strlen(buffer)] = '\0';
    int temp = 0;
    if (sharedDate == nullptr)
    {
        sharedDate = new Date;
    }
    fin >> temp;
    sharedDate->SetDay(temp);
    fin >> temp;
    sharedDate->SetMonth(temp);
    fin >> temp;
    sharedDate->SetYear(temp);
    fin.getline(buffer, 99);
    fin.getline(buffer, 99);
    if (Title == 0)
    {
        Title = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] Title;
        Title = new char[strlen(buffer) + 1];
    }
    strcpy(Title, buffer);
    Title[strlen(buffer)] = '\0';
}
void Post::AddComment(Comments* c)
{
    if (comments == 0)
    {
        comments = new Comments * [11];
        for (int i = 0; i < 11; i++)
        {
            comments[i] = nullptr;
        }
    }
    int i = 0;
    while (comments[i] != nullptr)
    {
        i++;
    }
    if (i == 10)
    {
        cerr << "No more comments can be added to the post!" << endl;
    }
    else
        comments[i] = c;
}
void Post::PrintPost()
{
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    sharedBy->PrintName();
    PrintSharedDate();
    cout << "\t\t\"" << Title << "\"" << endl;
    PrintComments();
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
class Page : public Object
{
    char* ID;
    char* Title;
    Post** Timeline;

public:
    Page();
    Post** GetTimeline();
    void PrintName();
    void AddToTimeline(Post*);
    void ViewTimeline();
    ~Page();
    void ReadDataFromFile(ifstream&);
    void printInfo();
    // getters
    char* GetID();
    char* GetTitle();
};
Page::Page()
{
    Timeline = nullptr;
    ID = nullptr;
    Title = nullptr;
}
Page::~Page()
{
    if (ID != 0)
    {
        delete[] ID;
    }
    if (Title != 0)
    {
        delete[] Title;
    }
    if (!Timeline)
    {
        delete[] Timeline;
    }
}
Post** Page::GetTimeline()
{
    return Timeline;
}
void Page::PrintName()
{
    cout << "\t       " << Title;
}
void Page::AddToTimeline(Post* p)
{
    if (Timeline == nullptr)
    {
        Timeline = new Post * [11];
        for (int i = 0; i < 11; i++)
        {
            Timeline[i] = nullptr;
        }
    }
    int index = 0;
    while (Timeline[index] != nullptr)
    {
        index++;
    }
    if (index == 10)
    {
        cerr << "No more Posts can be added to the Timeline!" << endl;
    }
    else
        Timeline[index] = p;
}
void Page::ViewTimeline()
{
    if (Timeline == 0)
    {
        cout << Title << " has no posts!" << endl;
        return;
    }
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << Title << endl
        << endl;
    for (int i = 0; Timeline[i] != nullptr; i++)
    {
        cout << Title;
        Timeline[i]->PrintActivity();
        cout << endl;
        cout << " Shared Date: ";
        Timeline[i]->PrintSharedDate();
        cout << "\t\"" << Timeline[i]->GetTitle() << "\"" << endl;
        Timeline[i]->PrintComments();
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
void Page::ReadDataFromFile(ifstream& fin)
{
    char buffer[50];
    fin >> buffer;
    if (ID == nullptr)
    {
        ID = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] ID;
        ID = new char[strlen(buffer) + 1];
    }
    strcpy(ID, buffer);
    ID[strlen(buffer)] = '\0';
    fin.getline(buffer, 49);
    if (Title == nullptr)
    {
        Title = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] Title;
        Title = new char[strlen(buffer) + 1];
    }
    strcpy(Title, buffer);
}
void Page::printInfo()
{
    cout << ID << " - " << Title << endl;
}
char* Page::GetID()
{
    return ID;
}
char* Page::GetTitle()
{
    return Title;
}
class Memory : public Post
{
private:
    Post* ptr;

public:
    Memory(const char*, Post*);
    Post* GetPostPtr();
};
Memory::Memory(const char* c, Post* p)
{
    ptr = p;
    this->SetTitle(c);
}
Post* Memory::GetPostPtr()
{
    return ptr;
}
class User : public Object
{
    char* ID;
    char* Fname;
    char* Lname;
    User** FriendList;
    Page** LikedPages;
    Post** Timeline;
    Memory** memories;

public:
    ~User();
    void ShareMemory(Post*, const char*);
    void ViewHome();
    Post** GetTimeline();
    void ViewMemories();
    User();
    void PrintName();
    void AddToTimeline(Post*);
    void ViewTimeline();
    void AddFriend(User*);
    void LikePage(Page*);
    void ReadDataFromFile(ifstream&);
    void ViewFriendList();
    void ViewLikedPages();
    void printInfo();
    // getters
    char* GetID();
    char* GetFname();
    char* GetLname();
};
char* User::GetFname()
{
    return Fname;
}
char* User::GetLname()
{
    return Lname;
}
char* User::GetID()
{
    return ID;
}
void User::printInfo()
{
    cout << ID << " - \t" << Fname << " " << Lname << endl;
}
void User::ViewLikedPages()
{
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << Fname << " " << Lname << " - "
        << "Liked Pages" << endl;
    if (LikedPages == nullptr)
    {
        cout << "This User has liked no Pages." << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        return;
    }
    for (int i = 0; LikedPages[i] != nullptr; i++)
    {
        cout << LikedPages[i]->GetID() << " - " << LikedPages[i]->GetTitle() << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
void User::ViewFriendList()
{
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << Fname << " " << Lname << " - "
        << "Friend List" << endl;
    if (FriendList == nullptr)
    {
        cout << "This User has no Friends." << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        return;
    }
    for (int i = 0; FriendList[i] != nullptr; i++)
    {
        cout << FriendList[i]->ID << " - " << FriendList[i]->Fname << " " << FriendList[i]->Lname << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
void User::ReadDataFromFile(ifstream& fin)
{
    char buffer[20];
    fin >> buffer;
    if (ID == nullptr)
    {
        ID = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] ID;
        ID = new char[strlen(buffer) + 1];
    }
    strcpy(ID, buffer);
    ID[strlen(buffer)] = '\0';
    fin >> buffer;

    if (Fname == nullptr)
    {
        Fname = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] Fname;
        Fname = new char[strlen(buffer) + 1];
    }
    strcpy(Fname, buffer);
    Fname[strlen(buffer)] = '\0';
    fin >> buffer;
    if (Lname == nullptr)
    {
        Lname = new char[strlen(buffer) + 1];
    }
    else
    {
        delete[] Lname;
        Lname = new char[strlen(buffer) + 1];
    }
    strcpy(Lname, buffer);
    Lname[strlen(buffer)] = '\0';
}
void User::LikePage(Page* p)
{
    if (p == nullptr)
    {
        return;
    }
    if (LikedPages == nullptr)
    {
        LikedPages = new Page * [11];
        for (int i = 0; i < 11; i++)
        {
            LikedPages[i] = nullptr;
        }
    }
    int i = 0;
    for (i = 0; LikedPages[i] != nullptr; i++)
        ;
    if (i >= 10)
    {
        cerr << "No more Pages can be liked." << endl;
    }
    LikedPages[i] = p;
}
void User::AddFriend(User* u)
{
    if (u == nullptr)
    {
        return;
    }
    if (FriendList == nullptr)
    {
        FriendList = new User * [11];
        for (int i = 0; i < 11; i++)
        {
            FriendList[i] = nullptr;
        }
    }
    int i = 0;
    for (i = 0; FriendList[i] != nullptr; i++)
        ;
    if (i >= 10)
    {
        cerr << "No more Friends can be added." << endl;
    }
    FriendList[i] = u;
}
void User::ViewTimeline()
{
    if (Timeline == 0)
    {
        cout << Fname << " " << Lname << " has no posts!" << endl;
        return;
    }
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << Fname << " " << Lname << " - Timeline:" << endl
        << endl;
    if (memories != nullptr)
    {
        for (int i = 0; memories[i] != nullptr; i++)
        {
            cout << "~~~ " << Fname << " " << Lname << " sahred a memory ~~~ (1h)" << endl;
            cout << "\t\"" << memories[i]->GetTitle() << "\"" << endl;
            cout << "\t~~~ ";
            if (memories[i]->GetPostPtr()->sharedDate->GetMonth() != Date::currMonth)
            {
                int temp = memories[i]->GetPostPtr()->sharedDate->GetMonth() - Date::currMonth;
                if (temp < 0)
                    temp *= -1;
                cout << temp << " Months ago";
            }
            else
            {
                if (memories[i]->GetPostPtr()->sharedDate->GetYear() != Date::currYear)
                {
                    int temp = memories[i]->GetPostPtr()->sharedDate->GetYear() - Date::currYear;
                    if (temp < 0)
                        temp *= -1;
                    cout << temp << " Years ago";
                }
                else
                {
                    cout << "1h ago";
                }
            }
            cout << " ~~~" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << Fname << " " << Lname;
            memories[i]->GetPostPtr()->PrintActivity();
            cout << endl;
            cout << "Shared Date: ";
            memories[i]->GetPostPtr()->PrintSharedDate();
            cout << "\t\"" << memories[i]->GetPostPtr()->GetTitle() << "\"" << endl;
            memories[i]->GetPostPtr()->PrintComments();
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
                << endl;
        }
    }
    for (int i = 0; Timeline[i] != nullptr; i++)
    {
        cout << Fname << " " << Lname;
        Timeline[i]->PrintActivity();
        cout << endl;
        cout << "Shared Date: ";
        Timeline[i]->PrintSharedDate();
        cout << "\t\"" << Timeline[i]->GetTitle() << "\"" << endl;
        Timeline[i]->PrintComments();
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
void User::AddToTimeline(Post* p)
{
    if (Timeline == 0)
    {
        Timeline = new Post * [11];
        for (int i = 0; i < 11; i++)
        {
            Timeline[i] = nullptr;
        }
    }
    int index = 0;
    while (Timeline[index] != nullptr)
    {
        index++;
    }
    if (index == 10)
    {
        cerr << "No more Posts can be added to the Timeline!" << endl;
    }
    else
        Timeline[index] = p;
}
void User::PrintName()
{
    cout << "\t\t" << Fname << " " << Lname;
}
User::User()
{
    ID = nullptr;
    Fname = nullptr;
    Lname = nullptr;
    FriendList = nullptr;
    LikedPages = nullptr;
    Timeline = 0;
    memories = nullptr;
}
User::~User()
{
    if (!ID)
    {
        delete[] ID;
    }
    if (!Lname)
    {
        delete[] Lname;
    }
    if (!Fname)
    {
        delete[] Fname;
    }
    if (!FriendList)
    {
        delete[] FriendList;
    }
    if (!LikedPages)
    {
        delete[] LikedPages;
    }
    if (!Timeline)
    {
        for (int i = 0; Timeline[i] != nullptr; i++)
        {
            delete[] Timeline;
        }
        delete[] Timeline;
    }
    if (!memories)
    {
        delete[] memories;
    }
}
void User::ShareMemory(Post* ptr, const char* buffer)
{
    if (this->GetTimeline() == nullptr)
    {
        cout << "\t\tCannot share memory as this user has no posts!" << endl;
        return;
    }
    if (memories == 0)
    {
        memories = new Memory * [11];
        for (int i = 0; i < 11; i++)
        {
            memories[i] = nullptr;
        }
    }
    bool postExist = false;
    for (int j = 0; Timeline[j] != nullptr; j++)
    {
        if (Timeline[j] == ptr)
        {
            postExist = true;
        }
    }
    if (postExist)
    {
        int i = 0;
        for (i = 0; memories[i] != nullptr; i++)
            ;
        if (i >= 10)
        {
            cerr << "No more memories can be shared!" << endl;
        }
        memories[i] = new Memory(buffer, ptr);
    }
    else
    {
        cerr << "This post does not exist in the user's timeline!" << endl;
    }
}
void User::ViewHome()
{
    int minRequiredDay = Date::currDay - 3;
    int maxRequiredDay = Date::currDay;
    int requiredMonth = Date::currMonth;
    int requiredYear = Date::currYear;
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << Fname << " " << Lname << " - Homepage" << endl
        << endl;
    if (Timeline != nullptr)
    {
        for (int i = 0; Timeline[i] != nullptr; i++)
        {
            if (Timeline[i]->sharedDate->GetDay() <= maxRequiredDay && Timeline[i]->sharedDate->GetDay() >= minRequiredDay && Timeline[i]->sharedDate->GetMonth() == requiredMonth && Timeline[i]->sharedDate->GetYear() == requiredYear)
            {
                cout << Fname << " " << Lname;
                Timeline[i]->PrintActivity();
                cout << endl;
                cout << "Shared Date: ";
                Timeline[i]->PrintSharedDate();
                cout << "\t\"" << Timeline[i]->GetTitle() << "\"" << endl;
                Timeline[i]->PrintComments();
                cout << endl;
            }
        }
    }
    if (FriendList != nullptr)
    {
        for (int i = 0; FriendList[i] != nullptr; i++)
        {
            if (FriendList[i]->GetTimeline() == nullptr)
            {
                continue;
            }
            for (int j = 0; FriendList[i]->Timeline[j] != nullptr; j++)
            {
                Post* p = FriendList[i]->Timeline[j];
                if (p->sharedDate->GetDay() <= maxRequiredDay && p->sharedDate->GetDay() >= minRequiredDay && p->sharedDate->GetMonth() == requiredMonth && p->sharedDate->GetYear() == requiredYear)
                {
                    cout << FriendList[i]->Fname << " " << FriendList[i]->Lname;
                    p->PrintActivity();
                    cout << endl;
                    cout << "Shared Date: ";
                    p->PrintSharedDate();
                    cout << "\t\"" << p->GetTitle() << "\"" << endl;
                    p->PrintComments();
                    cout << endl;
                }
            }
        }
    }
    if (LikedPages != nullptr)
    {
        for (int i = 0; LikedPages[i] != nullptr; i++)
        {
            Post** ptr = LikedPages[i]->GetTimeline();
            if (ptr == nullptr)
            {
                continue;
            }
            for (int j = 0; ptr[j] != nullptr; j++)
            {
                if (ptr[j]->sharedDate->GetDay() <= maxRequiredDay && ptr[j]->sharedDate->GetDay() >= minRequiredDay && ptr[j]->sharedDate->GetMonth() == requiredMonth && ptr[j]->sharedDate->GetYear() == requiredYear)
                {
                    cout << LikedPages[i]->GetTitle();
                    ptr[j]->PrintActivity();
                    cout << endl;
                    cout << "Shared Date: ";
                    ptr[j]->PrintSharedDate();
                    cout << "\t\"" << ptr[j]->GetTitle() << "\"" << endl;
                    ptr[j]->PrintComments();
                    cout << endl;
                }
            }
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
Post** User::GetTimeline()
{
    return Timeline;
}
void User::ViewMemories()
{
    Post** p = this->GetTimeline();
    if (p == nullptr)
    {
        cout << "\tThis user has no posts!" << endl;
        return;
    }
    for (int i = 0; p[i] != nullptr; i++)
    {
        for (int j = 0; p[j] != nullptr; j++)
        {
            if (p[i]->sharedDate->GetDay() < p[j]->sharedDate->GetDay())
            {
                Post* temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
    for (int i = 0; p[i] != nullptr; i++)
    {
        for (int j = 0; p[j] != nullptr; j++)
        {
            if (p[i]->sharedDate->GetMonth() < p[j]->sharedDate->GetMonth())
            {
                Post* temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
    for (int i = 0; p[i] != nullptr; i++)
    {
        for (int j = 0; p[j] != nullptr; j++)
        {
            if (p[i]->sharedDate->GetYear() < p[j]->sharedDate->GetYear())
            {
                Post* temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
    cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl;
    for (int i = 0; p[i] != nullptr; i++)
    {
        cout << "\nOn this Day" << endl;
        if (p[i]->sharedDate->GetDay() != Date::currDay)
        {
            int temp = p[i]->sharedDate->GetDay() - Date::currDay;
            if (temp < 0)
                temp *= -1;
            cout << temp << " Days ago" << endl;
        }
        else
        {
            if (p[i]->sharedDate->GetMonth() != Date::currMonth)
            {
                int temp = p[i]->sharedDate->GetMonth() - Date::currMonth;
                if (temp < 0)
                    temp *= -1;
                cout << temp << " Months ago" << endl;
            }
            else
            {
                if (p[i]->sharedDate->GetYear() != Date::currYear)
                {
                    int temp = p[i]->sharedDate->GetYear() - Date::currYear;
                    if (temp < 0)
                        temp *= -1;
                    cout << temp << " Years ago" << endl;
                }
                else
                {
                    cout << "1h ago" << endl;
                }
            }
            cout << Fname << " " << Lname;
            p[i]->PrintActivity();
            cout << endl;
            cout << "\t\"" << p[i]->GetTitle() << "\"" << endl;
            p[i]->PrintComments();
            cout << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
}
class Controller
{

    User** AllUsers;
    Page** AllPages;
    Post** AllPosts;
    User* currentUser;
    char** commands;
    bool userStatus;
    Comments** comments;

public:
    Controller();
    ~Controller();
    static bool IsSubStringInString(const char*, const char*);
    User* SearchUserByID(char[]);
    Page* SearchPageByID(char[]);
    Post* SearchPostByID(char[]);

    void LoadAllUsers(ifstream&);
    void LoadAllPages(ifstream&);
    void LinkUsersAndPages(ifstream&);
    void LoadAllPosts(ifstream&);
    void LoadCommands(ifstream&);
    void LoadComments(ifstream&);
    void LinkActivites(ifstream&);
    void LoadData();
    bool CommandChecker(const char*, int&);
    void CommandLoader(const char*&, char*&);
    void exe(const char*);
    void run();
};
Controller::Controller()
{
    AllUsers = 0;
    AllPages = 0;
    AllPosts = 0;
    currentUser = 0;
    commands = 0;
    userStatus = 0;
    comments = 0;
}
Controller::~Controller()
{
    if (AllUsers != 0)
    {
        delete[] AllUsers;
    }
    if (AllPages != 0)
    {
        delete[] AllPages;
    }
    if (AllPosts != 0)
    {
        delete[] AllPosts;
    }
    if (commands != 0)
    {
        int i = 0;
        for (i = 0; commands[i] != nullptr; i++)
        {
            delete[] commands[i];
        }
        delete[] commands[i];
        delete[] commands;
    }
    if (comments != 0)
    {
        delete[] comments;
    }
}
bool Controller::IsSubStringInString(const char* str, const char* substr)
{
    int substrIndex = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == substr[substrIndex])
        {
            if (substr[substrIndex + 1] == '\0')
            {
                return 1;
            }
            substrIndex++;
            continue;
        }
        else
        {
            substrIndex = 0;
        }
    }
    return 0;
}
User* Controller::SearchUserByID(char id[20])
{
    for (int i = 0; AllUsers[i] != nullptr; i++)
    {
        if (IsSubStringInString(AllUsers[i]->GetID(), id))
        {
            return AllUsers[i];
        }
    }
    return nullptr;
}
Page* Controller::SearchPageByID(char id[20])
{
    for (int i = 0; AllPages[i] != nullptr; i++)
    {
        if (IsSubStringInString(AllPages[i]->GetID(), id))
        {
            return AllPages[i];
        }
    }
    return nullptr;
}
Post* Controller::SearchPostByID(char id[20])
{
    for (int i = 0; AllPosts[i] != nullptr; i++)
    {
        if (IsSubStringInString(AllPosts[i]->GetID(), id))
        {
            return AllPosts[i];
        }
    }
    return nullptr;
}
void Controller::LoadAllUsers(ifstream& fin)
{
    int total = 0;
    fin >> total;
    AllUsers = new User * [total + 1];
    int i = 0;
    for (i = 0; i < total; i++)
    {
        AllUsers[i] = new User;
        AllUsers[i]->ReadDataFromFile(fin);
    }
    AllUsers[i] = nullptr;
}
void Controller::LoadAllPages(ifstream& fin)
{
    int total = 0;
    fin >> total;
    AllPages = new Page * [total + 1];
    int i = 0;
    for (i = 0; i < total; i++)
    {
        AllPages[i] = new Page;
        AllPages[i]->ReadDataFromFile(fin);
    }
    AllPages[i] = nullptr;
}
void Controller::LinkUsersAndPages(ifstream& fin)
{
    char buffer[20];
    while (!fin.eof())
    {
        fin >> buffer;
        User* temp = SearchUserByID(buffer);
        while (!IsSubStringInString("-1", buffer))
        {
            fin >> buffer;
            if (IsSubStringInString("-1", buffer))
                break;
            temp->AddFriend(SearchUserByID(buffer));
        }
        fin >> buffer;
        while (!IsSubStringInString("-1", buffer))
        {
            temp->LikePage(SearchPageByID(buffer));
            fin >> buffer;
            if (IsSubStringInString("-1", buffer))
                break;
        }
    }
}
void Controller::LoadAllPosts(ifstream& fin)
{
    char buffer[50];
    int total = 0;
    fin >> total;
    AllPosts = new Post * [total + 1];
    int i = 0;
    Object* temp = nullptr;
    for (i = 0; i < total; i++)
    {
        if (temp != nullptr)
            temp = nullptr;
        AllPosts[i] = new Post;
        AllPosts[i]->ReadDataFromFile(fin);
        fin >> buffer;
        temp = SearchUserByID(buffer);
        if (temp == 0)
        {
            temp = SearchPageByID(buffer);
        }
        AllPosts[i]->AddSharedBy(temp);
        temp->AddToTimeline(AllPosts[i]);
        fin >> buffer;
        while (!IsSubStringInString("-1", buffer))
        {
            temp = nullptr;
            temp = SearchUserByID(buffer);
            if (temp == nullptr)
            {
                temp = SearchPageByID(buffer);
            }
            AllPosts[i]->AddLikedBy(temp);
            fin >> buffer;
        }
    }
    AllPosts[i] = nullptr;
}
void Controller::LoadCommands(ifstream& fin)
{
    int total = 0;
    fin >> total;
    if (commands == 0)
    {
        commands = new char* [total + 1];
        for (int i = 0; i < total; i++)
        {
            commands[i] = nullptr;
        }
    }
    char buffer[50];
    fin.getline(buffer, 49);
    int i = 0;
    while (!fin.eof())
    {
        fin.getline(buffer, 49);
        commands[i] = new char[strlen(buffer) + 1];
        strcpy(commands[i], buffer);
        i++;
    }
    commands[total] = nullptr;
}
void Controller::LoadComments(ifstream& fin)
{
    int total = 0;
    fin >> total;
    if (comments == nullptr)
    {
        comments = new Comments * [total + 1];
    }
    char buffer[100];
    int i = 0;
    for (i = 0; i < total; i++)
    {
        fin >> buffer;
        comments[i] = new Comments;
        comments[i]->SetId(buffer);
        fin >> buffer;
        Post* temp = SearchPostByID(buffer);
        comments[i]->SetPostId(temp);
        fin >> buffer;
        Object* temp2 = nullptr;
        temp2 = SearchUserByID(buffer);
        if (temp2 == nullptr)
        {
            temp2 = SearchPageByID(buffer);
        }
        comments[i]->SetCommentBy(temp2);
        fin.getline(buffer, 99);
        comments[i]->SetCommentDescription(buffer);
        temp->AddComment(comments[i]);
    }
    comments[i] = nullptr;
}
void Controller::LinkActivites(ifstream& fin)
{
    int total = 0;
    int tempInt = 0;
    char buffer[50];
    Post* temp2;
    fin >> total;
    for (int i = 0; i < total; i++)
    {
        Activity* temp = new Activity;
        fin >> buffer;
        temp2 = SearchPostByID(buffer);
        fin >> tempInt;
        temp->SetType(tempInt);
        fin.getline(buffer, 49);
        temp->SetValue(buffer);
        temp2->SetActivity(temp);
    }
}
void Controller::LoadData()
{
    ifstream fin("Users.txt");
    LoadAllUsers(fin);
    LoadAllPages(fin);
    LinkUsersAndPages(fin);
    fin.close();
    fin.open("Posts.txt");
    LoadAllPosts(fin);
    fin.close();
    fin.open("Commands.txt");
    LoadCommands(fin);
    fin.close();
    fin.open("Comments.txt");
    LoadComments(fin);
    fin.close();
    fin.open("Activities.txt");
    LinkActivites(fin);
    fin.close();
}
bool Controller::CommandChecker(const char* c, int& commandNumber)
{
    for (int i = 0; commands[i] != nullptr; i++)
    {
        if (IsSubStringInString(c, commands[i]))
        {
            commandNumber = i + 1;
            return true;
        }
    }
    commandNumber = -1;
    return false;
}
void Controller::CommandLoader(const char*& command, char*& buffer)
{
    int i = 0;
    int j = 0;
    for (i = 0; command[i] != '\0'; i++)
    {
        if (command[i] == '(')
        {
            break;
        }
    }
    if (command[i] == '\0' || command[i + 1] == ' ' || command[i + 1] == '\0' || command[i + 1] == ')')
    {
        cerr << "Command's description is incomplete" << endl;
        return;
    }
    i++;
    while (command[i] != ')')
    {
        if (command[i] == '\0' || command[i] == ',')
        {
            break;
        }
        buffer[j] = command[i];
        j++;
        i++;
    }
    buffer[j] = '\0';
}
void Controller::exe(const char* command)
{
    cout << "\nCommand:\t" << command << endl;

    int commandNumber = -1;
    if (!CommandChecker(command, commandNumber))
    {
        cerr << "Invalid Command!" << endl;
        // cin.clear();
        // cin.ignore();
        return;
    }
    else
    {
        char* buffer = new char[10];
        if (commandNumber == 1)
        {
            CommandLoader(command, buffer);
            User* temp = SearchUserByID(buffer);
            if (temp == nullptr)
            {
                cout << "User not found!" << endl;
            }
            else
            {
                currentUser = temp;
                userStatus = true; // active
                cout << endl;
                cout << currentUser->GetFname() << " " << currentUser->GetLname() << " successfully set as Current User" << endl;
            }
        }
        if (commandNumber == 2)
        {
            if (userStatus == 0)
            {
                cout << "No active current Users" << endl;
            }
            else
            {
                currentUser->ViewFriendList();
            }
        }
        if (commandNumber == 3)
        {
            if (userStatus == 0)
            {
                cout << "No active current Users" << endl;
            }
            else
            {
                currentUser->ViewLikedPages();
            }
        }
        if (commandNumber == 4)
        {
            if (userStatus == 0)
            {
                cout << "No active current Users" << endl;
            }
            else
            {
                currentUser->ViewTimeline();
            }
        }
        if (commandNumber == 5)
        {
            CommandLoader(command, buffer);
            Post* temp = SearchPostByID(buffer);
            if (temp == 0)
            {
                cerr << "Invalid Post Id!" << endl;
            }
            else
            {
                temp->PrintLikedBy();
            }
        }
        if (commandNumber == 6)
        {
            CommandLoader(command, buffer);
            Post* temp = SearchPostByID(buffer);
            Object* userPtr = currentUser;
            if (userStatus == 0)
            {
                cout << "No active current Users" << endl;
            }
            else if (temp == nullptr)
            {
                cerr << "Invalid Post ID!" << endl;
            }
            else
            {
                temp->AddLikedBy(userPtr);
            }
        }
        if (commandNumber == 7)
        {
            CommandLoader(command, buffer);
            Page* temp = SearchPageByID(buffer);
            if (temp == 0)
            {
                cerr << "Invalid Page Id!" << endl;
            }
            else
            {
                temp->ViewTimeline();
            }
        }
        if (commandNumber == 8)
        {
            char choice;
        again:
            cout << "Are you sure you want to exit the application? (y,n)" << endl;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Have a good day! Later." << endl;
                exit(0);
            }
            else if (choice == 'n' || choice == 'N')
            {
                cin.clear();
                cin.ignore();
                return;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
                goto again;
            }
        }
        if (commandNumber == 9)
        {
            CommandLoader(command, buffer);
            Post* temp = SearchPostByID(buffer);
            Object* userPtr = currentUser;
            if (userStatus == 0)
            {
                cerr << "No Active current Users!" << endl;
            }
            else
            {
                int i = 0;
                while (command[i] != ',')
                {
                    if (command[i] == '\0')
                    {
                        cerr << "Command description is incomplete!" << endl;
                        cin.clear();
                        cin.ignore();
                        return;
                    }
                    i++;
                }
                i++;
                int j = 0;
                while (command[i] != ')')
                {
                    buffer[j] = command[i];
                    i++;
                    j++;
                }
                buffer[j] = '\0';
                Comments* temp2 = new Comments;
                temp2->SetCommentDescription(buffer);
                temp2->SetCommentBy(userPtr);
                temp->AddComment(temp2);
            }
        }
        if (commandNumber == 10)
        {
            CommandLoader(command, buffer);
            Post* temp = SearchPostByID(buffer);
            if (temp == 0)
            {
                cerr << "Invalid Post Id!" << endl;
            }
            else
            {
                temp->PrintPost();
            }
        }
        if (commandNumber == 11)
        {
            Date::SetCurrentDate(17, 4, 2024);
            cout << "\nSystem Date: ";
            Date::PrintCurrDate();
        }
        if (commandNumber == 12)
        {
            if (currentUser == nullptr)
            {
                cout << "User not found!" << endl;
            }
            else
            {
                currentUser->ViewHome();
            }
        }
        if (commandNumber == 13)
        {
            if (currentUser == nullptr)
            {
                cout << "User not found!" << endl;
            }
            else if (userStatus == 0)
            {
                cout << "No Active current Users!" << endl;
            }
            else
            {
                currentUser->ViewMemories();
            }
        }
        if (commandNumber == 14)
        {
            CommandLoader(command, buffer);
            Post* temp = SearchPostByID(buffer);
            if (userStatus == 0)
            {
                cerr << "No Active current Users!" << endl;
            }
            else
            {
                int i = 0;
                while (command[i] != ',')
                {
                    if (command[i] == '\0')
                    {
                        cerr << "Command description is incomplete!" << endl;
                        cin.clear();
                        cin.ignore();
                        return;
                    }
                    i++;
                }
                i++;
                int j = 0;
                while (command[i] != ')')
                {
                    buffer[j] = command[i];
                    i++;
                    j++;
                }
                buffer[j] = '\0';
                currentUser->ShareMemory(temp, buffer);
            }
        }
        delete[] buffer;
    }
}
void Controller::run()
{
    this->exe("set current user (u7)");
    this->exe("set current date");
    this->exe("view homepage");
    this->exe("view friend list");
    this->exe("view liked pages");
    this->exe("view timeline");
    this->exe("view liked list (post5)");
    this->exe("like post (post5)");
    this->exe("view liked list (post5)");
    this->exe("view page (p1)");
    this->exe("view homepage");
    this->exe("post comment(post4,Good Luck for your result)");
    this->exe("view post(post4)");
    this->exe("post comment(post8,Thnaks for the wishes)");
    this->exe("view post(post8)");
    this->exe("see your memories");
    this->exe("share memory(post10,Never thought i will be a specialist in this field)");
    this->exe("view timeline");
}
int main()
{
    Controller mainApp;
    mainApp.LoadData();
    char command[100];
    cout << "\n\t\t--------------------> Welcome to the Social Network App! <--------------------" << endl
        << endl;
    // mainApp.run();

    while (true)
    {
        cout << "\n Command: ";
        cin.getline(command, 99);
        mainApp.exe(command);
    }
}