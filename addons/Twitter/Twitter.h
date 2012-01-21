#ifndef ROXLU_TWITTERH
#define ROXLU_TWITTERH

#include <vector>
#include <string>
#include <fstream>

#include "../../libs/curl/curl.h"
#include "../../libs/crypto/urlencode.h"

#include "parameter/Collection.h"
#include "parameter/Parameter.h"
#include "curl/Request.h"
#include "curl/Curl.h"
#include "oauth/Utils.h"
#include "oauth/oAuth.h"

namespace rtc = roxlu::twitter::curl;
namespace rtp = roxlu::twitter::parameter;
namespace rto = roxlu::twitter::oauth;

using std::string;
using std::vector;


// This implementation is based on twitcurl with some modifications for OF
// All hard work goes to the author of TwitCurl!

namespace roxlu {
namespace twitter {

const string URL_STATUSES_BASE = "https://api.twitter.com/1/statuses/";
const string URL_FRIENDSHIPS_BASE = "https://api.twitter.com/1/friendships/";
const string URL_DIRECT_MESSAGES_BASE = "https://api.twitter.com/1/direct_messages/";
const string URL_FOLLOWERS_BASE = "https://api.twitter.com/1/followers/";
const string URL_USERS_BASE = "https://api.twitter.com/1/users/";

const string URL_STATUSES_RETWEETED_BY = "/retweeted_by.json";
const string URL_STATUSES_RETWEETED_BY_IDS = "/retweeted_by/ids.json";
const string URL_STATUSES_RETWEETS = URL_STATUSES_BASE +"retweets/";
const string URL_STATUSES_SHOW = URL_STATUSES_BASE +"show.json";
const string URL_STATUSES_DESTROY = URL_STATUSES_BASE +"destroy/";
const string URL_STATUSES_RETWEET = URL_STATUSES_BASE +"retweet/";
const string URL_STATUSES_UPDATE = URL_STATUSES_BASE +"update.json";
const string URL_STATUSES_UPDATE_WITH_MEDIA = URL_STATUSES_BASE +"update_with_media.json";
const string URL_STATUSES_OEMBED = URL_STATUSES_BASE +"oembed.json";

const string URL_STATUSES_HOME_TIMELINE = URL_STATUSES_BASE +"home_timeline.json";
const string URL_STATUSES_MENTIONS = URL_STATUSES_BASE +"mentions.json";
const string URL_STATUSES_PUBLIC_TIMELINE = URL_STATUSES_BASE +"public_timeline.json";
const string URL_STATUSES_RETWEETED_BY_ME = URL_STATUSES_BASE +"retweeted_by_me.json";
const string URL_STATUSES_RETWEETED_TO_ME = URL_STATUSES_BASE +"retweeted_to_me.json";
const string URL_STATUSES_RETWEETS_OF_ME = URL_STATUSES_BASE +"retweets_of_me.json";
const string URL_STATUSES_USER_TIMELINE = URL_STATUSES_BASE +"user_timeline.json";
const string URL_STATUSES_RETWEETED_TO_USER = URL_STATUSES_BASE +"retweeted_to_user.json";
const string URL_STATUSES_RETWEETED_BY_USER = URL_STATUSES_BASE +"retweeted_by_user.json";

const string URL_SEARCH = "https://search.twitter.com/search.json";

const string URL_DIRECT_MESSAGES = "https://api.twitter.com/1/direct_messages.json";
const string URL_DIRECT_MESSAGES_SENT = URL_DIRECT_MESSAGES_BASE +"sent.json";
const string URL_DIRECT_MESSAGES_DESTROY = URL_DIRECT_MESSAGES_BASE +"destroy/";
const string URL_DIRECT_MESSAGES_NEW = URL_DIRECT_MESSAGES_BASE +"new.json";
const string URL_DIRECT_MESSAGES_SHOW = URL_DIRECT_MESSAGES_BASE +"show/"; 

const string URL_FOLLOWERS_IDS = URL_FOLLOWERS_BASE +"ids.json";
const string URL_FRIENDS_BASE = "https://api.twitter.com/1/friends/";
const string URL_FRIENDS_IDS = URL_FRIENDS_BASE +"ids.json";
const string URL_FRIENDSHIPS_EXISTS = URL_FRIENDSHIPS_BASE +"exists.json";
const string URL_FRIENDSHIPS_INCOMING = URL_FRIENDSHIPS_BASE +"incoming.json";
const string URL_FRIENDSHIPS_OUTGOING = URL_FRIENDSHIPS_BASE +"outgoing.json";
const string URL_FRIENDSHIPS_SHOW = URL_FRIENDSHIPS_BASE +"show.json";
const string URL_FRIENDSHIPS_CREATE = URL_FRIENDSHIPS_BASE +"create.json";
const string URL_FRIENDSHIPS_DESTROY = URL_FRIENDSHIPS_BASE +"destroy/";
const string URL_FRIENDSHIPS_LOOKUP = URL_FRIENDSHIPS_BASE +"lookup.json";
const string URL_FRIENDSHIPS_UPDATE = URL_FRIENDSHIPS_BASE +"update.json";
const string URL_FRIENDSHIPS_NO_RETWEET_IDS = URL_FRIENDSHIPS_BASE +"no_retweet_ids.json";

const string URL_USERS_LOOKUP = URL_USERS_BASE +"lookup.json";
const string URL_USERS_SEARCH = URL_USERS_BASE +"search.json";
const string URL_USERS_SHOW = URL_USERS_BASE +"show.json";
const string URL_USERS_CONTRIBUTEES = URL_USERS_BASE +"contributees.json";
const string URL_USERS_CONTRIBUTORS = URL_USERS_BASE +"contributors.json";



const string URL_AUTHORIZE = "http://twitter.com/oauth/authorize?oauth_token=";


class Twitter {
public:
	Twitter();
	~Twitter();

	bool requestToken(string& authURL /* out */);
	bool accessToken();
	bool handlePin(const string& authURL); 
	bool setPin(const string& pin);
	
	void setTwitterUsername(const string& username);
	void setTwitterPassword(const string& password);
	
	void setConsumerKey(const string& consumerKey);
	void setConsumerSecret(const string& consumerSecret);
	
	bool saveTokens(const string& filePath);
	bool loadTokens(const string& filePath);
	bool removeTokens(const string& filePath);
	
	// API: Tweets
	bool statusesRetweetedBy(const string& tweetID, rtp::Collection* extraParams =  NULL);
	bool statusesRetweetedByIDs(const string& tweetID, rtp::Collection* extraParams = NULL);
	bool statusesRetweets(const string& tweetID, rtp::Collection* extraParams = NULL);
	bool statusesShow(const string& tweetID, rtp::Collection* extraParams = NULL);
	bool statusesDestroy(const string& tweetID, rtp::Collection* extraParams = NULL); 
	bool statusesRetweet(const string& tweetID, rtp::Collection* extraParams = NULL);
	bool statusesUpdate(const string& tweet, rtp::Collection* extraParams =  NULL);
	bool statusesUpdateWithMedia(const string& tweet, const string& imageFilePath, rtp::Collection* extraParams =  NULL);
	bool statusesoEmbed(const string& tweetID, rtp::Collection* extraParams =  NULL); 
	
	
	// API: Timelines
	bool statusesHomeTimeline(rtp::Collection* extraParams =  NULL);
	bool statusesMentions(rtp::Collection* extraParams =  NULL);
	bool statusesPublicTimeline(rtp::Collection* extraParams =  NULL);
	bool statusesRetweetedByMe(rtp::Collection* extraParams = NULL);
	bool statusesRetweetedToMe(rtp::Collection* extraParams = NULL);
	bool statusesRetweetsOfMe(rtp::Collection* extraParams = NULL);
	bool statusesUserTimeline(rtp::Collection* extraParams = NULL);
	bool statusesRetweetedToUser(const string& screenName, rtp::Collection* extraParams = NULL);
	bool statusesRetweetedByUser(const string& screenName, rtp::Collection* extraParams = NULL);
	
	// API: search
	bool search(const string& query, rtp::Collection* extraParams = NULL);

	// API: search (your Twitter application needs to have permissions!)
	bool directMessages(rtp::Collection* extraParams = NULL);
	bool directMessagesSent(rtp::Collection* extraParams = NULL);
	bool directMessagesDestroy(const string& messageID, rtp::Collection* extraParams = NULL);
	bool directMessagesNew(const string& screenName, const string& text, rtp::Collection*  extraParams = NULL);
	bool directMessagesShow(const string& messageID);
	
	// API: Friends & followers
	bool followersIDs(const string& screenName, rtp::Collection* extraParams = NULL);
	bool friendsIDs(const string& screenName, rtp::Collection* extraParams = NULL);
	bool friendshipsExists(const string& screenNameA, const string& screenNameB);
	bool friendshipsIncoming(rtp::Collection* extraParams = NULL);
	bool friendshipsOutgoing(rtp::Collection* extraParams = NULL);
	bool friendshipsShow(const string& sourceScreenName, const string& targetScreenName);
	bool friendshipsCreate(const string& screenName, rtp::Collection* extraParams = NULL);
	bool friendshipsDestroy(const string& screenName, rtp::Collection* extraParams = NULL);
	bool friendshipsLookup(const string& screenNames);
	bool friendshipsUpdate(const string& screenName, bool enableDeviceNotifications, bool enableRetweets);
	bool friendshipsNoRetweetIDs(bool stringifyIDs = true);
	
	// API: Users
	bool usersLookup(const string& screenNames, rtp::Collection* extraParams = NULL);
	bool usersSearch(const string& q, rtp::Collection* extraParams = NULL);
	bool usersShow(const string& screenName, rtp::Collection* extraParams = NULL);
	bool usersContributees(const string& screenName, rtp::Collection* extraParams = NULL);
	bool usersContributors(const string& screenName, rtp::Collection* extraParams = NULL);
	//bool usersProfileImages();  // how do we implement this.. maybe parse the 302
	
	// ++
	
	
	

	
	
/*
	bool getMentions();
	bool getPublicTimeline();
	bool getRetweetedByMe();
	bool getRetweetedToMe();
	bool getRetweetsOfMe();
	bool getUserTimeline();
	*/
	string& getResponse();	
	
private:
	bool doGet(const string& url, rtp::Collection* defaultParams = NULL, rtp::Collection* extraParams = NULL);
	bool doPost(const string& url, const rtp::Collection& col, bool multiPart = false, rtp::Collection* extraParams = NULL);
	bool doPost(const string& url, bool multiPart = false, rtp::Collection* extraParams = NULL);
	void reset();
	string response;
	rto::oAuth oauth;
	rtc::Curl twitcurl;
};

inline bool Twitter::doGet(const string& url, rtp::Collection* defaultParams, rtp::Collection* extraParams) {
	reset();
	rtc::Request req(url);
	req.isGet(true);
	
	if(defaultParams != NULL) {
		req.getParams() += *defaultParams;
	}
		
	if(extraParams != NULL) {
		req.getParams() += *extraParams;
	}
	
	
	oauth.authorize(req);
	return req.doGet(twitcurl, response);
}


inline bool Twitter::doPost(const string& url, bool multiPart, rtp::Collection* extraParams) {
	reset();
	rtc::Request req(url);
	if(extraParams != NULL) {
		req.getParams() += *extraParams;
	}
	req.isPost(true);
	oauth.authorize(req);
	return req.doPost(twitcurl, response, multiPart);

}

inline bool Twitter::doPost(const string& url, const rtp::Collection& col, bool multiPart, rtp::Collection* extraParams) {	
	reset();
	rtc::Request req(url);
	req.addParams(col);
	if(extraParams != NULL) {
		req.getParams() += *extraParams;
	}
	req.isPost(true);
	oauth.authorize(req);
	return req.doPost(twitcurl, response, multiPart);
}




inline void Twitter::setTwitterUsername(const string& username) {
	twitcurl.setAuthUsername(username);
}

inline void Twitter::setTwitterPassword(const string& password) {
	twitcurl.setAuthPassword(password);
}

inline void Twitter::setConsumerKey(const string& key) {
	oauth.setConsumerKey(key);
}

inline void Twitter::setConsumerSecret(const string& secret) {
	oauth.setConsumerSecret(secret);
}

inline string& Twitter::getResponse() {
	return response;
}
	
}} // roxlu twitter

#endif
