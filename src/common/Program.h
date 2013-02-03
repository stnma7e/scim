#ifndef PROGRAM_H_
#define PROGRAM_H_

namespace scim
{

class Program
{
public:
	enum ProgramStatus
	{
		UNINITIALIZED, // If a Program is not RUNNING || STOPPED, then it is assumed to be UNINITIALIZED
		RUNNING,
		STOPPED
	};
protected:
	ProgramStatus m_programStatus;
public:
	virtual ~Program() { }

	virtual bool Init() = 0;
	virtual void OnUpdate(F64 dtime) = 0;
	virtual void Shutdown() = 0;

	virtual ProgramStatus GetStatus() { return m_programStatus; }
};

}
#endif