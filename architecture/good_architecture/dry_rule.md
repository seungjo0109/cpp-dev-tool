## The Dry rule
* DRY is short for "don't repeat yourself." It means you should avoid code duplication and reuse when it's possible.
* This means you should extract a function or a function template when your code repeats similar operations a few times. Also, instead of creating several similar types, you should consider writing a template.

</br>

* It's also important not to reinvent the wheel when it's not necessary, that is, not to repeat other's work.
* Nowdays there are dozens of well-written and mature libraries that can help you with writing high-quality software faster.

</br>
    
* [Boost C++ Libraries](https:/​/www.​boost.​org/​)
* [Facebook's Folly](https:/​/github.​com/​facebook/​folly)
* [Electronic Arts' EASTL](https:/​/github.​com/​electronicarts/​EASTL)
* [Bloomberg's BDE](https:/​/github.​com/​bloomberg/​bde)
* [Google's Abseil](https:/​/abseil.io/​)
* [The Awesome Cpp list](https:/​/github.​com/​fffaraz/​awesome-​cpp) 

</br>

* Sometimes duplicating code can have its benefits, however. One such scenario is developing microservices. 
* Of coursre, it's always a good idea to follow DRY inside a single microservice, but violating the DRY rule for code used in multiple services can acually be worth it.
* Whether we're talking about model entities or logic, it's easier to maintain miltiple services when code duplication is allowed.

</br>

* Imagine having multiple microservices reusing the same code for an entitiy.
* Suddenly one of them needs to modify one field. All the other services now have to be modified as well.
* The same goes for dependencies of any common code. 
* With dozens or more microservices that have to be modified because of changes unrelated to them, it's often easier for maintenance to just duplicate the code.