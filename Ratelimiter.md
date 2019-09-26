### Rate limiter

This project includes a implementation of a rate limiting system written in C++. This "rate limiter" will provide interfaces to create new "limiters" and invoke certain functions on them like "increment" and "get". The naming of these functions are subject to change. The system also provides various configurations for the type of limiter to use. These include simple counters to other counting structures we might have use for in the future(based on how the scope of this project changes).

But, why and when would we use such a feature?

#### Why a rate limiter?

First of all, why would we include another piece of software in our already complex system?

The need of a rate limiting system surfaces when the invocation of any particular procedure at a high rate would cause performace degradation in the system. This procedure can be computationally expensive, or it could easily be a simple procedure, but with high amounts of request being invoked upon it.

Another use of rate limiting is for security contingencies. When you offer a service to a client, any client could misuse the api and make high request load that is above the average threshold, hence, resulting in putting load on our machines. 

So the rate limiting service could be used in any type of server software running with high load.

#### What is a rate limiter?

So the rate limiter would be a separate running service that keeps tracks of requests being made to any other another services. It would have internal counters and other data structures, however complex based on the requirements, to monitor the use of the other services. It essentially limits the rate of requests that are made to the services by rejecting or throwing exeptions on the excess requests.

Since we use a rate limiter with other services as a addition, by requirements it should be very high performant and should not result in **any** significant overhead in performance and normal functionality of the original service. 



#### Scenarious of use

1. Single machine, single threaded - single limiter
2. Single machine, multi threaded - single limiter
3. Distributed machines - single limiter
4. Distributed machines - distributed limiter



#### How does a rate limiter work? 

There are different well established strategies for building a rate limiter, like

1. Token bucket algorithm
2. Leaky bucket algorithm
3. Fixed Window Counters
4. Sliding Window Logs
5. Sliding Window Counters

Source: https://www.figma.com/blog/an-alternative-approach-to-rate-limiting/



#### Token bucket algorithm

In this approach, we keep track of each unique user's available token count and their last request timestamp. We store them in the same hash. 

```json
{
  "user_1" : {
    "tokens" : 5,
    "timestamp" : 1569503968
  }
}
```



When we make a new request, the first thing we do is, refill the tokens based on 2 things:

- The refill rate that is set up
- The time of the last request

Then, we would update the hash with current request timestamp and available token count.

When the available token count drops to **zero**, the rate limiter knows the user has exceeded their limits.

A simple implementation of this would be trivial. It would also have a small memory footprint and the algorithm is straightforward.



Resources to look for rate limiting:



https://stripe.com/blog/rate-limiters

https://www.figma.com/blog/an-alternative-approach-to-rate-limiting/

https://cloud.google.com/solutions/rate-limiting-strategies-techniques

https://www.alexedwards.net/blog/how-to-rate-limit-http-requests

https://blog.cloudflare.com/counting-things-a-lot-of-different-things/

https://medium.com/smyte/rate-limiter-df3408325846

https://konghq.com/blog/how-to-design-a-scalable-rate-limiting-algorithm/

https://hechao.li/2018/06/25/Rate-Limiter-Part1/

https://news.ycombinator.com/item?id=15962701

https://nordicapis.com/stemming-the-flood-how-to-rate-limit-an-api/

https://dzone.com/articles/building-a-distributed-rate-limiter-that-scales-ho

https://blog.atulr.com/rate-limiter/ ?? Wtf is this

https://www.youtube.com/watch?v=FU4WlwfS3G0&feature=youtu.be

https://en.wikipedia.org/wiki/Token_bucket

Some simple examples:

https://github.com/smyte/ratelimit

https://medium.com/@saisandeepmopuri/system-design-rate-limiter-and-data-modelling-9304b0d18250



Enterprise rate limiting services:

https://www.cloudflare.com/rate-limiting/



https://www.nginx.com/blog/rate-limiting-nginx/