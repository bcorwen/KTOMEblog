[Dev blog](devblog.md) | [Project aims and goals](goals.md) | [Project to-do](todo.md) | [Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK) | [KTANE IRL Discord server](https://discord.com/channels/711013430575890432)

---

# Dev blog
I'm currently making short update videos on progress on [my Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK). It's certainly much quicker to film/narrate what's new than type up a new blog post! Check there for more up-to-date info, meanwhile a more detailed write-up will appear here going into much more detail.

---

[Prev post: Coding Passwords and Morse](devblog_11.md)

## 2022/05/03 - Building the case
More catch-up with prior progress - this post covers progress in July 2021 and very slowly onwards.

### Case Concept

So on to the bomb case.

My design owes a lot to Syber and Miracoulon, two of the other builders on the Discord. They had the great idea to build their cases from aluminium extrusion, which really looks the part, is strong and very customisable. My only exposure to this was when I put together my 3D printer, so understood only some very basics, but managed to learn enough from looking through online stores that I felt confident enough to put together a plan.

Knowing the sizes of the modules, I tried to pick a size of extrustion to appear proportional, looked into the options for that size (e.g. rounded corners and smooth, flat faces on some sides), and knocked it up in CAD to visualise how it would look. The only real variables left would be the depth of the modules and how the modules connected - physically and electrically.

> ![Bomb case CAD](https://i.imgur.com/9ShPnQB.png)
> 
> The initial design of the bomb case

Instead of going for a simple frame, I went for a more complex (and much heavier) two layer design:
- The inner section would house the modules and help the user guide them in place.
- The outer section would house the widgets, and is designed a little thicker than the inner section to give the face of the bomb a recessed appearance.

Most of the extrusion along the outside would have smooth faces, with only the grooves on the inside to attach the extrusions to one another. This helps keep the look clean and simple.

Without a solid plan for how the modules connect, I placed the order for the initial pieces and got to work

### Initial build

> ![Case extrustions pre-build](https://i.imgur.com/o9OyhRl.jpg)
> 
> The initial case extrustions pre-assembly

It was a lot tougher to bolt the extrusions together than I thought it would, and this was in part due to the difficulty in keeping the corners as close to right-angles as I could - over-tightening an L-bracket would pull the pieces together.

> ![The inner case](https://i.imgur.com/S3HfLdX.jpg)
> 
> The inner case only...

> ![The outer case front](https://i.imgur.com/XolBxrz.jpgg)
> 
> Then adding on the outer case

> ![The outer case side](https://i.imgur.com/1jr54XS.jpg)
> 
> And the view from the side

It looks great! This project is almost looking professional...

One big change at this point was to the modules themselves. The original modules, which entirely fit within the 130mm height and width looked completely lost in the case! They were just too small. I ended up redesigning the modules to be a little larger (good for having to fit in the components), leaving the edges of the faces to stick out over the inner case. This would stop the modules being pushed too far inside. Win-win! The modules also changed from having 8 grooves on the sides (designed to help the modules slide in place into the frame) to just 4. To make use of the 8 would have required much more of an extrusion lattice on the inside, and the current mass of extrusion was totalling about 6kg! You may notice a difference in themodule boxes between the module design post and photos shown further down...

### Back-plates and Connections

Sometime later, Miracoulon again came in with some great suggestions to help me design the physical and electrical connectors. I initially wanted a back-plate that the modules would be pushed into, where connectors would match up and allow power and signals to reach the modules. I wasn't sure how to actually design this in, and started to instead look into loose cabling that would have to be attached to the modules before sliding them in place. This brought up a whole heap more questions about how this would work without having a tangle of cables inside and whiloe making it user friendly to people other than myself. Mira and I brainstormed the back-plate idea again and came up with more 3D printing to save the day.

> ![Design of the back plate](https://i.imgur.com/APkyNPH.png)
> 
> Design of the back-plate

The plates would be made up of two identical halves. There was a space for an electrical connector (I went with a serial DB-9 connector, as I had 5 planned lines and the possibility of needing more in future) and I made it quite hollow to allow cabling. There were magnet holders to physically hold the modules in place. And the plates would be held into the case with more L-brackets.

> ![Back-plate](https://i.imgur.com/dtITiYP.jpg)
> 
> The finished back-plate

> ![Back-plate and module](https://i.imgur.com/Zwc86AK.jpg)
> 
> A back-plate and a module

These worked perfectly. As both the modules and back-plates were designed in CAD, both the magnetic and electrical conncetors married up exactly. Sliding the modules in and out of the case was smooth and easy.

> ![Modules in the case](https://i.imgur.com/HSCafps.jpg)
> 
> Two modules back-to-back, sandwiching a back-plate

### Wrapping up

This all happened over the course of a few months. It took a lot of time to build, disassemble, reassemble, etc the case when I needed to make a major adjustment or addition. But it was all starting to come together and I could see what the finished product might actually look like.

There was still a lot of work to be done just on the case. The outer frame was not attached to the inner case for the majority of the time as the widgets and side panels had not been concepted yet, and big questions remained over how this would best be done. So I'll save that story for a later post...

[Prev post: Coding Passwords and Morse](devblog_11.md)
