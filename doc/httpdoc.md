<!--
 * @Author: your name
 * @Date: 2021-03-18 10:58:39
 * @LastEditTime: 2021-03-18 11:01:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/doc/httpdoc.md
-->

# HTTP

> host/path

## POST

**普通**

```
httplib::Client cli([host cStringUsingEncoding:NSUTF8StringEncoding]);

NSString *pstr = [pdict yy_modelToJSONString];
auto ret = cli.Post([path cStringUsingEncoding:NSUTF8StringEncoding], [pstr cStringUsingEncoding:NSUTF8StringEncoding], "application/json");

if (ret.error() == httplib::Error::Success) {
    if (ret->status == 200) { // http success
        auto res =  ret.value();
        
        std::string &data = res.body;
        
        NSString *dstr = [NSString stringWithCString:data.c_str() encoding:NSUTF8StringEncoding];
        
        INFO(@"dstr = %@", dstr);
    } else { // http error
    }
} else { // tcp error
}
```

**携带头**

```
httplib::Client cli([host cStringUsingEncoding:NSUTF8StringEncoding]);
        
httplib::Headers headers = httplib::Headers();
for (NSString *k in hdict) {
    headers.insert( std::make_pair([k UTF8String], [hdict[k] UTF8String]) );
}

//        httplib::make_range_header({{1, 10}});
//        httplib::Params params;
//        params.emplace("name", "john");
//        params.emplace("note", "coder");

auto ret = cli.Post([path cStringUsingEncoding:NSUTF8StringEncoding], headers, [pstr cStringUsingEncoding:NSUTF8StringEncoding], "application/json");

if (ret.error() == httplib::Error::Success) {
    if (ret->status == 200) { // http success
        auto res =  ret.value();
        
        std::string &data = res.body;
        
        NSString *dstr = [NSString stringWithCString:data.c_str() encoding:NSUTF8StringEncoding];
        
        INFO(@"dstr = %@", dstr);
    } else { // http error
    }
} else { // tcp error
}
```