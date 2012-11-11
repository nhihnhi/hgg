#ifndef _BUSMASTERCARDLOGIC_H_
#define _BUSMASTERCARDLOGIC_H_

#include "BusmasterCardLogic.h"
#include "Backplane.h"

class BusmasterCardLogicImpl : public BusmasterCardLogic {
public:
	BusmasterCardLogicImpl(BusmasterCardPHY& phy);
	virtual ~BusmasterCardLogicImpl();

	/// \brief the core loop doing all the work
	virtual void loop();


	enum eBMCLIState {
		BMCLIS_Init,
		BMCLIS_Error,
		BMCLIS_Enumerate,
		BMCLIS_SendEnumerationQuery,
		BMCLIS_WaitForEnumerationAnswer,
		BMCLIS_EnumerationTimeout,
		BMCLIS_Idle
	};

	eBMCLIState getState() const;

	const char* getStateString() const;

	Backplane& 	getBackplane() { return _bp; }

protected:
	/// \brief finds out which cards need to be enumerated.
	void				handleEnumeration();

	/// \brief sends an enumeration query message.
	void				handleSendEnumerationQuery();

	/// \brief waits for the answer on the enumeration and handles it.
	void				handleWaitForEnumerationAnswer();

	/// \brief cleanup after a failed enumeration.
	void        handleEnumerationTimeout();

	/// \brief get the number of encountered bus errors
	int         getBusErrorCount();

private:
	void setState(eBMCLIState s);
	eBMCLIState _state;

	Backplane _bp;

	int	_enumerationCounter;
	int _busErrorCounter;
	uint32_t _tickCountMarker;

  FRIEND_TEST(BusmasterCardLogic, EnumerationFailureWhenEnumerationAnswerIsMissing);
  FRIEND_TEST(BusmasterCardLogic, EnumerationOfCardTimesOut);
};


#endif //_BUSMASTERCARDLOGIC_H_

