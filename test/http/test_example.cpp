#include <iostream>
#include <algorithm>
#include <iterator>
#include <gtest/gtest.h>
#include <boost/program_options.hpp>

namespace boost_test
{

  namespace po = boost::program_options;
  using namespace std;

  class ProgramOptionsTest : public testing::Test
  {
  protected:
    static void SetUpTestCase()
    {
    }

    static void TearDownTestCase()
    {
    }
  };
  TEST_F(ProgramOptionsTest, Test1)
  {
    int opt;
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "product help message")("optimization_level", po::value<int>(&opt)->default_value(10))("include-dir,I", po::value<vector<string>>(), "include path");

    // a.out --optimization_level 2 -I"c:/boost/include", "gtest/include"
    const char *argv[] = {"a.out", "--optimization_level", "2", "-I", "c:/boost/include", "-I", "gtest/include"};
    int argc = 7;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    ASSERT_EQ(vm.count("help"), 0);
    ASSERT_EQ(vm.count("optimization_level"), 1);
    ASSERT_EQ(vm["optimization_level"].as<int>(), 2);
    ASSERT_EQ(opt, 2);
    ASSERT_EQ(vm.count("include-dir"), 1);

    const vector<string> vct = vm["include-dir"].as<vector<string>>();
    ASSERT_EQ(vct.size(), 2);
    ASSERT_EQ(vct[0], "c:/boost/include");
    ASSERT_EQ(vct[1], "gtest/include");
  };