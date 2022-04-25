## Exploring the fundamentals of good architecture

* It's important to know to recognize a good architecture from a bad one, but it's not an easy task.
* Recognizing anti-pattern is an important aspect of it, but for an architecture to be good, primarily it has to supprot delivering what's expected from the software, whether it's about functional requirements, attributes of the solution, or dealing with the constraints coming from various places. Many of those can be easily derived from the architecture context.

</br>

### Architecture context
* The context is what an archtect takes into account when designing a solid solution.
* It comprises requirements, assumptions, and constraints, which can come from the stakeholders, as well as the business and technical environments.
* It also influences the stakeholders and the environments, for example, by allowing the company to enter a new market segment.

</br>

### Stakeholders
* Stakeholders are all the people that are somehow involved with the product.
* Those can be your customers, the users of your system, or the management.
* Communication is a key skill for every archtect and properly managing your stakeholder's needs is key to delivering what they expected and in a way they wanted. 

</br>

* Different things are important to different groups of stakeholders, so try gather input from all those groups.
* Your customers will probably care about the cost of writing and running the software, the functionality it delivers, its lifetime, time to market, and the quality of your solution.
* The users of your system can be divided into two groups: end users and administrators.
* The first ones usually care about things such as the usability, user experience, and performance of the software. For the latter, more important aspects are user management, system configuration, security, backups, and recovery.
* Finally, things that could matter for stakeholders working in management are keeping the development sots low, achieving business goals, being on track with the development schedule, and maintaining product quality.


</br>

### Business and technical environments
* Architecture can be influenced by the business of the company. Important related apsects are the time to merket, the rollout schedule, the organizational structure, utilization of the workforce, and investment in existing assets.

</br>

* By technical environment, we mean the technologies already used in a company or those that are for any reason required to be part of the solution.
* Other systems that we need to integrate with are also a vital part of the technical environment.
* THe technical expertise of the available software enginerrs is of importance here, too: the technological decisions an architect makes can impact staffing the project, and the ratio of junior to senior developers can influence how a project should be govened.
* __Good architecture should take all of that into accout.__

</br>

### Developing architecture using Agile principles
* Seemingly, architecture and Agile developemnt methodolgies are in an adversarial relationship, and there are many myths around this topic.
* There are a few simple principles that you should follow in order to develop your product in an Agile way while still caring about its architecture.

</br>

* Agile, by nature, is iterative and incremental. This means preparing a big, upfront design is not an option in an Agile approach to architecture. Instead, a small, but still reasonable upfront design should be proposed.
* It's best if it comes with a log of decisions with a log of decisions with the rationale for each of them.
* This way, if the product vision changes, the architecture can evolve with it.
* To support frequent release delivery, the upfront design should teh be updated incrementally. Archtecture developed this way is called evolutionary architecture.

</br>

* Managing architecture doesn't need to mean keeping massive documentation. In fact, document should cover only what's essential as this way it's easier to keep it up to date. It should be simple and cover only the relevant views of the system.

</br>

* An architect should remain part of the development team as often they're bringing stroing technical expertise and years of experience to the table.
* They should also take part in making extimations and plan the architecture changes needed before each iteration.
* In order for your team to remain Agile, you should think of ways to work efficiently and only what's important.
* A good idea to embrace to achieve those goals is domain-driven design.

</br>

### Domain-driven design
* Domain-driven design, or DDD for short, __it's about improving communication between business and engineering and bringing the developers' attention to the domain model.__
* Basing the implementation of this model often leads to designs that are easier to understand and evolve together with the model changes.

</br>

* What has DDD got to do with Agile?
    * __Individuals and interactions__ over processes and tools
    * __Working software__ over comprehensive documentation
    * __Customer collaboration__ over contract negotiation
    * __Responding to change__ over following a plan

</br>

* In order to make the proper design decisions, you must understand the domain first.
* To do so, you'll need to talk to people a lot and encourage your developer teams to narrow the gap between them and business people.
* The conecpts in the code should be named after entities that are part of `ubiquitous language`.
* Countless misunderstandings can be caused by each of these groups using terms that the other understands differently, leading to laws in business logic implementations and often subtle bugs.
* Naming things with care and using terms agreed by both groups can mean for the projects.

</br>

* If you're modeling a bigger system, it might be hard to make all the terms mean the same to different teams. This is because each of those teams really operates in a different context.
* DDD proposes the use of `bounded contexts` to deal with this. If you're modeling, say, an e-commerce system, you might want to think of the terms just in terms of a shopping context, but upon a closer look, you may discover that the inventory, delivery, and accounting temas actually all have their own models and terms.

</br>

* Each of those is a different subdomain of your e-commerce domain. Ideally, each can be mapped to its own bounded context - a part of your system with its own vocabulary.
* It's important to set clear boundaries of such contexts when splitting your solution into smaller modules.
* Just like its context, each module has clear reposibilites, its own database schema, and its own code base.
* To help communicate between the teams in larger systems, you might want to introduce a context map, which will show how the terms from diffrent contexts relate to each other.

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20