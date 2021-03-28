/*
 * @Author: your name
 * @Date: 2021-03-26 17:30:01
 * @LastEditTime: 2021-03-27 16:04:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/timber/test_timber_async.cc
 */

#include <gtest/gtest.h>
#include <future>
#include "timber/mt_timber.h"

// using ::testing::_;
// using ::testing::AtLeast;                     // #1
// using ::testing::Ge;
// using ::testing::NotNull;
// using ::testing::StrictMock;
// using ::testing::StartsWith;


// The fixture for testing class Project1. From google test primer.
class AsyncIOTests : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

    // AsyncIOService *aioService;

	AsyncIOTests()

    {
		// You can do set-up work for each test here.
        // aioService = AsyncIOService::getInstance();        
	}

	virtual ~AsyncIOTests() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.

};


// class AsyncIOHttpCallback {
// public:
//     virtual void onData(char *data, size_t datalen) {};

//     virtual void onFinish(double content_length, long header_size, long httpcode, char *redirect_url) {};

//     virtual void onError(CURLcode curlErrorNo) {};

//     virtual void onTimeout() {};

//     virtual ~AsyncIOHttpCallback() {}
// };

// class MockCallback : public AsyncIOHttpCallback {
// public:
//     MOCK_METHOD1(onError, void(CURLcode errCode));
//     MOCK_METHOD0(onTimeout, void());
//     MOCK_METHOD2(onData, void(char *data, size_t datalen));
//     MOCK_METHOD4(onFinish, void(double content_length, long header_size, long httpcode, char *redirect_url));
// };

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
// TEST_F(AsyncIOTests, DoSampleHTTPFetch) {
//     shared_ptr<AsyncIOHttpContext>  url1(new AsyncIOHttpContext);
//     shared_ptr<MockCallback>    mcallback(new StrictMock<MockCallback>);

//     shared_ptr<AsyncIORequestPolicy> policy(new AsyncIORequestPolicy);

//     policy->finishHandler = [&mcallback](double  content_length, long header_size, long httpcode, char *redirect_url) {
//         EXPECT_EQ(httpcode, 200);
//         mcallback->onFinish(content_length, header_size, httpcode, redirect_url);
//     };
//     std::string url = "http://www.baidu.com";
//     url1->url = url;

//     policy->errorHandler = [&mcallback] (CURLcode curlError) {
//         mcallback->onError(curlError);
//     };
//     policy->timeoutHandler = [&mcallback]() {
//         mcallback->onTimeout();
//     };

//     // aioService->queueHttpRequest(policy);

//     // EXPECT_CALL((*mcallback.get()), onFinish(_,_, _, NULL)).Times(1);

//     // aioService->waitRequestEmpty(5);
// }


void helloFunction(const std::string& s) {
    std::cout << "Hello C++11 from " + s + ".";
}

TEST(timber, async)
{
    logd("async debug message");

    // std::promise<void> started;
    // EXPECT_CALL(mock, start_test())
    //     .Times(1)
    //     .WillOnce(testing::Invoke([&started]() {
    //         started.set_value();
    //     }));
    // system_->start();
    // EXPECT_EQ(std::future_status::ready, started.get_future().wait_for(std::chrono::seconds(3)));

    logd("async debug message");

    std::async([](){

        logd("async debug 3 message");
        logi("async info  3 message");
        logw("async warn  3 message");
        loge("async error 3 message");
    });

    std::async(helloFunction, "function object");


    std::future<int> f1 = std::async(std::launch::async, [](){ 
        return 8;  
    }); 

    std::cout<<f1.get()<< std::endl; //output: 8

    std::future<int> f2 = std::async(std::launch::async, [](){ 

        logd("async debug 4 message");
        logi("async info  4 message");
        logw("async warn  4 message");
        loge("async error 4 message");

        std::cout<<8<< std::endl;

        return 1;
    }); 

    std::chrono::milliseconds span(2000);
    if (f2.wait_for(span) == std::future_status::timeout) {
        loge("timeout here");
    }

    // sleep(2);
}

// int main(int argc, char** argv) {
// 	// The following line must be executed to initialize Google Mock
// 	// (and Google Test) before running the tests.

//     ::testing::InitGoogleTest(&argc, argv);
// 	::testing::InitGoogleMock(&argc, argv);
// 	return RUN_ALL_TESTS();
// }