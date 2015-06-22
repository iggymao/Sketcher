#ifndef _LogManager_H
#define _LogManager_H

#include <GL/glew.h>   
#include <string>

#define LOG_FILE "logs/log.log"					// a log file for general information
#define GL_LOG_FILE "logs/opengl.log"				// a logfile for opengl related items

#define LOG_TYPE_UNDEFINED	-1				// default log type
#define LOG_TYPE_MAIN		 0				// default for the main logs
#define LOG_TYPE_OPENGL		 1				// default for the opengl log

// linked list showing Shader information (Type of Shader, Type of Texture, etc.)
struct LogInfo
{
	int LogID;					// unique identifier for each shader
	int LogType;				// type of log as identified in LogManager.h
	std::string strLogFilename;		// stores the name and location of the files being read.
	LogInfo *next;				// point to the next ShaderItem
};

class LogManager
{
public:
	LogManager();
	~LogManager() {Destroy();}

	LogInfo *MemberInfo;			// a linked list of each of the known log types
	LogInfo *firstMemberInfo;		// a pointer to the last entry
	LogInfo *lastMemberInfo;		// a pointer to the last entry

	void Initialize();				// initializes the log manager

	void AddLog(struct LogInfo *head, int type, std::string logfilename);			// adds a log to the linked list

	void SetID(int id_num) { LogManagerID = id_num; }
	int GetID() { return LogManagerID;}

	// search for a ShaderInfo entry based the frag and vert file name.
	struct LogInfo *searchLogInfo(struct LogInfo *MemberInfo, int logtype);
	void ShowDetails(struct LogInfo *head);		// Shows all the items currently known by the shader manager.
	void deleteLinkedList(struct Loginfo *MemberInfo);	// deletes the entire linked MemberInfo list;

	bool restart_logs();			// initializes the log files
	void gl_log_params();
	bool gl_log (char *filename, char* message, ...); 
	//void glfw_error_callback (int error, const char* description);
	//bool gl_log_err (const char* message, ...);

	void Destroy();

private:
		int LogManagerID;

};

#endif