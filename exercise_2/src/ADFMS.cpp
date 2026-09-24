/***********************************************************************
 * Project    : Autonomous Drone Fleet Management System (ADFMS)
 * Module     : Flight Controller
 * Version    : 1.3.2
 *
 * Description:
 * This software controls autonomous medical delivery drones.
 * It authenticates operators, validates missions,
 * executes drone commands and records mission activities.
 *
 * NOTE:
 * This software is intentionally developed as part of a
 * Secure Software Code Review laboratory exercise.
 *
 * Organization:
 * SkyFleet Technologies
 *
 ***********************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

/***********************************************************************
 * USER CLASS
 ***********************************************************************/
class User
{
private:

    string username;
    string password;
    string role;

public:

    User(string u,string p)
    {
        username = u;
        password = p;

        // Default role assigned after login
        role = "Operator";
    }

    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }

    string getRole() const
    {
        return role;
    }

    void setRole(string r)
    {
        role = r;
    }
};

/***********************************************************************
 * AUTHENTICATION CLASS
 ***********************************************************************/
class Authentication
{
private:

    string validUser = "pilot1";
    string validPassword = "Drone@123";

public:

    bool authenticate(User& user);

    bool login(User& user);

    string getRole(User& user);
};


bool Authentication::authenticate(User& user)
{
    if(user.getUsername()==validUser &&
       user.getPassword()==validPassword)
    {
        return true;
    }

    return false;
}

bool Authentication::login(User& user)
{
    cout<<"Authenticating Operator..."<<endl;

    if(authenticate(user))
    {
        cout<<"Login Successful"<<endl;
        return true;
    }

    cout<<"Authentication Failed"<<endl;

    return false;
}

string Authentication::getRole(User& user)
{
    return user.getRole();
}

/***********************************************************************
 * MISSION CLASS
 ***********************************************************************/
class Mission
{
private:

    int missionID;
    string destination;
    double altitude;
    double payloadWeight;

public:

    Mission(int id,
            string dest,
            double alt,
            double payload);

    bool validateMission();

    int getMissionID() const;

    string getDestination() const;

    double getAltitude() const;

    double getPayloadWeight() const;
};


Mission::Mission(int id,
                 string dest,
                 double alt,
                 double payload)
{
    missionID=id;
    destination=dest;
    altitude=alt;
    payloadWeight=payload;
}

bool Mission::validateMission()
{
    if(altitude<=0)
        return false;

    if(payloadWeight<0)
        return false;

    return true;
}

int Mission::getMissionID() const
{
    return missionID;
}

string Mission::getDestination() const
{
    return destination;
}

double Mission::getAltitude() const
{
    return altitude;
}

double Mission::getPayloadWeight() const
{
    return payloadWeight;
}

/***********************************************************************
 * LOGGER CLASS
 ***********************************************************************/
class Logger
{
public:

    Logger();

    void logEvent(const string& eventType,
                  const string& username,
                  const string& message);

    void logError(const string& message);

    string currentTime();
};


Logger::Logger()
{
}

string Logger::currentTime()
{
    time_t now=time(0);

    char* dt=ctime(&now);

    return string(dt);
}

void Logger::logEvent(const string& eventType,
                      const string& username,
                      const string& message)
{
    cout<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"Time : "<<currentTime();
    cout<<"Type : "<<eventType<<endl;
    cout<<"User : "<<username<<endl;
    cout<<"Info : "<<message<<endl;
    cout<<"------------------------------------------"<<endl;
}

void Logger::logError(const string& message)
{
    cout<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"Time : "<<currentTime();
    cout<<"ERROR : "<<message<<endl;
    cout<<"------------------------------------------"<<endl;
}

/***********************************************************************
 * FLIGHT CONTROLLER CLASS
 ***********************************************************************/
class FlightController
{
private:

    Authentication auth;
    Logger logger;

    bool missionActive;

public:

    FlightController();

    bool executeMission(User& user,
                        Mission& mission);

    bool authorizeMission(User& user);

    bool validateMission(Mission& mission);

    int calculatePayload(Mission& mission);

    bool sendMission(Mission& mission);

    void emergencyStop();

    void getTelemetry();

    bool abortMission(string reason);
};

/***********************************************************************
 * FlightController Implementation
 ***********************************************************************/

FlightController::FlightController()
{
    missionActive = false;
}

/***********************************************************************
 * Verify user authorization.
 ***********************************************************************/
bool FlightController::authorizeMission(User& user)
{
    if(user.getRole() == "Operator")
    {
        return true;
    }

    return false;
}

/***********************************************************************
 * Validate mission.
 ***********************************************************************/
bool FlightController::validateMission(Mission& mission)
{
    return mission.validateMission();
}

/***********************************************************************
 * Calculate payload.
 ***********************************************************************/
int FlightController::calculatePayload(Mission& mission)
{
    int totalPayload;

    totalPayload = mission.getPayloadWeight();

    // Packaging weight
    totalPayload += 5;

    return totalPayload;
}

/***********************************************************************
 * Upload mission to drone.
 ***********************************************************************/
bool FlightController::sendMission(Mission& mission)
{
    char destination[20];

    strcpy(destination,
           mission.getDestination().c_str());

    cout << endl;
    cout << "Uploading Mission..." << endl;

    cout << "Mission ID   : "
         << mission.getMissionID()
         << endl;

    cout << "Destination  : "
         << destination
         << endl;

    cout << "Altitude     : "
         << mission.getAltitude()
         << " meters" << endl;

    missionActive = true;

    return true;
}

/***********************************************************************
 * Emergency Stop
 ***********************************************************************/
void FlightController::emergencyStop()
{
    missionActive = false;

    cout << endl;
    cout << "*** EMERGENCY STOP ACTIVATED ***"
         << endl;
}

/***********************************************************************
 * Retrieve telemetry.
 ***********************************************************************/
void FlightController::getTelemetry()
{
    cout << endl;

    cout << "========== Drone Telemetry =========="
         << endl;

    cout << "Battery     : 91%" << endl;
    cout << "GPS         : Locked" << endl;
    cout << "Altitude    : Stable" << endl;

    cout << "Mission     : ";

    if(missionActive)
        cout << "ACTIVE";
    else
        cout << "IDLE";

    cout << endl;
}

/***********************************************************************
 * Abort Mission
 ***********************************************************************/
bool FlightController::abortMission(string reason)
{
    cout << endl;
    cout << "Mission Aborted." << endl;

    cout << "Reason : "
         << reason
         << endl;

    emergencyStop();

    return false;
}

/***********************************************************************
 * Complete Mission Execution Pipeline
 ***********************************************************************/
bool FlightController::executeMission(User& user,
                                      Mission& mission)
{
    cout << endl;
    cout << "======================================" << endl;
    cout << " AUTONOMOUS DRONE MISSION EXECUTION " << endl;
    cout << "======================================" << endl;

    //--------------------------------------------------
    // Step 1 : Authenticate
    //--------------------------------------------------

    if(!auth.authenticate(user))
    {
        logger.logError("Authentication failed for user : "
                        + user.getUsername());

        return false;
    }

    cout << "Authentication Successful." << endl;

    //--------------------------------------------------
    // Step 2 : Authorization
    //--------------------------------------------------

    if(!authorizeMission(user))
    {
        logger.logError("Authorization Failed.");

        return false;
    }

    cout << "Authorization Successful." << endl;

    //--------------------------------------------------
    // Step 3 : Mission Validation
    //--------------------------------------------------

    if(!validateMission(mission))
    {
        logger.logError("Mission Validation Failed.");

        return false;
    }

    cout << "Mission Validation Successful."
         << endl;

    //--------------------------------------------------
    // Step 4 : Payload Calculation
    //--------------------------------------------------

    int payload = calculatePayload(mission);

    cout << "Verified Payload : "
         << payload
         << " kg"
         << endl;

    //--------------------------------------------------
    // Step 5 : Upload Mission
    //--------------------------------------------------

    if(!sendMission(mission))
    {
        logger.logError("Mission Upload Failed.");

        return false;
    }

    //--------------------------------------------------
    // Step 6 : Telemetry
    //--------------------------------------------------

    getTelemetry();

    //--------------------------------------------------
    // Step 7 : Completion
    //--------------------------------------------------

    cout << endl;
    cout << "Mission Completed Successfully."
         << endl;

    return true;
}


/***********************************************************************
 * MAIN PROGRAM
 ***********************************************************************/
int main()
{
    cout << endl;
    cout << "==========================================" << endl;
    cout << " Autonomous Drone Fleet Management System " << endl;
    cout << "==========================================" << endl;

    User operator1("pilot1",
                   "Drone@123");

    Mission mission1(
            1001,
            "CityHospital",
            120,
            18.5);

    FlightController controller;

    if(controller.executeMission(operator1,
                                 mission1))
    {
        cout << endl;
        cout << "Mission Execution Successful."
             << endl;
    }
    else
    {
        cout << endl;
        cout << "Mission Execution Failed."
             << endl;
    }

    return 0;
}