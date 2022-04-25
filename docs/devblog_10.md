[Dev blog](devblog.md) | [Project aims and goals](goals.md) | [Project to-do](todo.md) | [Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK) | [KTANE IRL Discord server](https://discord.com/channels/711013430575890432)

---

# Dev blog
I'm currently making short update videos on progress on [my Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK). It's certainly much quicker to film/narrate what's new than type up a new blog post! Check there for more up-to-date info, meanwhile a more detailed write-up will appear here going into much more detail.

---

[Prev post: The Wires module](devblog_09.md)

## 2022/04/25 - Let's get physical
Wow, ok... it's been a long time since the last update. I hit a long run of momentum on the project and didn't want to slow down to write up these blog posts, but then forgot when things settled down once again.
This post is a short catch-up for June 2021

As mentioned in the previous post, I've been building up the electronics on breadboards and updating the code from the prototype. This progress was good but I was tired of the messy wires and had difficulty in showing some interesting updates. I decided it was time to park the coding and focus on the physical design of the bomb.

### Starting the design
My goal is to replicate the look and feel of the game as far as is possible, so I sat down with the aim of slavishly copying the module design.

It had been a while since I did some CAD (and even back then it was fairly basic stuff) but got to grips with Fusion 360 fairly quickly to produce a blank template module:

> ![Module template](https://i.imgur.com/JmkDDSH.png)
> 
> CAD model of a blank module

The design follows the same dimensions as the prototype: 130mm x 130mm x 70mm module boxes, with the face of the module extending beyond that 70mm deep box.

I added some rails along the sides of the module box, thinking these could be used to both act as a guide rail when inserting the modules into the case, as well as providing a good spot for the bolts that will attach the faceplate to the box (visible in the next photo).

Pretty happy with the design, I next needed to master the 3D printer which I'd not used to print many of my own designed before, so there was some additional patience needed between the long print times and making refinements. But the end result was pretty good!

> ![Printed blank module](https://i.imgur.com/jIO5Kj7.jpg)
> 
> The printed blank module - This was done in PETG which I've since stopped using in favour of PLA

And lastly, after looking for cheap fairy lights to repurpose, I decided to try to print the incidator light, which also turned out really well. Printing transparent items doesn't usually come out looking very clear, but the diffuse, translucent result was perfect to catch the light for this print:

> ![Test of the printed indicator light](https://i.imgur.com/EsCsnif.jpg)
> 
> Test of the printed indicator light, with an RGB LED showing how well it illuminates!

### Designing and printing Simon

So I had my blank module template. Time to cut some holes in it and stick in those arcade buttons. Easy, right?

Nup.

In the original design, the wooden modules took up all of that 130mm x 130mm spcae. Now, however, the modules aren't exactly square due to having tabs and other decorative parts, meaning the usable area is a little smaller. Even the few mm lost meant that the arcade buttons would not fit on the face of the module.

> ![Arcade buttons not fitting the module](https://i.imgur.com/01xHdh5.jpg?1)
> 
> The arcade buttons were simply too wide to fit the new module design

I like a good challenge, so decided I could CAD and print my way out of this problem. Instead of using the plastic button housings as provided, which have a lot of space around them, I could CAD this complex shape and reduce the margins to squeeze the 4 buttons in closer together. This took so, so many attempts to get just right (as I had to attempt to dimension small features I couldn't reach with my callipers and refine small and sensitive features such as the spring holder and clips for the arcade switches) but I eventually had a printed piece which you could pop the arcade buttons and switched into!

> ![Test showing the first attempt](https://i.imgur.com/SqmcD6D.jpg)
> 
> Showing the original button housing (right) and printed recreation (left)
> 
> ![Test showing two buttons](https://i.imgur.com/bz3KSaS.jpg)
> 
> Test showing two buttons fitted

And after finally getting a working button housing piece, it was ready to bolt together and the first module was printed!

> ![Finished Simon design](https://i.imgur.com/yS3nrTJ.jpg)
> 
> Finished Simon design!

### Designing and printing the Timer

Next, on to something a little different. The Timer looks like no other, so I wanted to tackle this unique design next.

The challenge here was another tight squeeze to make things fit. The original 130mm module size was picked as it was the tightest size for both the Simon buttons and the Timer's timer. The timer display is 120mm wide, and leaving some space for a 10mm border (plus some creative packing to make good use of space), this would just work. The timer comes with a preceeding colon which is not needed for Keep Talking, so the timer could be designed to clip into the frame to both save space and hide the colon:


> ![Timer from the front](https://i.imgur.com/g59ZtjN.jpg)
> 
> Timer from the front
> 
> ![Timer from back](https://i.imgur.com/NqmGZGk.jpg)
> 
> Timer from the back, showing the efficient use of space

The rest of the module was following the design of the original, including a similar frame around the 14-segment strike display. Then it was time to print and bolt everything together.

> ![Timer displays held in with braces](https://i.imgur.com/LencYf3.jpg)
> 
> The displays were held in place with some printed brace parts.
> 
> ![Finished Timer](https://i.imgur.com/5oC0l6c.jpg)
> 
> The finished Timer.

The Timer would get a similar but shorter module box, making the black face sunken into the case. The original design looks a little ambiguous about whether the face of the Timer module is black or simply hidden in a shadow.

### Conclusion

So as hinted earlier, these parts were primarily printed with PETG as I thought it would be a tougher choice of material, however I found it much harder to work with than PLA and PLA turned out to be tough enough. Plus, PLA comes in many more colours so I decided to just stick with PLA only in future.

There was also a revision to the guiding rails on the module boxes, as well as more design choices and the physical and electrical connectors... but I know I couldn't solve these issues until I knew more about the bomb case and how the modules would fit into the case.

It was time to pause progress on module printing and tackle the big picture - how to build the case.

[Prev post: The Wires module](devblog_09.md)
