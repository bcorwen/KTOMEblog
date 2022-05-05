[Dev blog](devblog.md) | [Project aims and goals](goals.md) | [Project to-do](todo.md) | [Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK) | [KTANE IRL Discord server](https://discord.com/channels/711013430575890432)

---

# Dev blog
I'm currently making short update videos on progress on [my Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK). It's certainly much quicker to film/narrate what's new than type up a new blog post! Check there for more up-to-date info, meanwhile a more detailed write-up will appear here going into much more detail.

---

[Prev post: Building the case](devblog_12.md)

## 2022/05/05 - Building The Button and Keypad
Yet more catch-up with prior progress - this post covers progress from August to September 2021.

### The Button

This was a very tricky module to design and print. Although the components I needed to integrate are fairly simple (only the button and an RGB LED), copying the look of the game meant this would need  a lot of complex parts.

For the LED, as I was used to using the chunky LEDs, it made sense to design a light box that the LED poked into. Similarly to a prior post describing how the transparent PLA used to make the module indicator bulb turning out diffuse and translucent, this same plastic could be printed on the front of the light box so as to catch the light and make a great diffuser.

The grey PLA I was using as the main module colour turned out to be slightly transparent itself however, so I covered the inside of the light box in aluminium tape to stop unwanted light leakage. This surprisingly made a big difference in the amount of light that made it to the front where it should be seen.

The last issue for the light box was how to attach it to the front of the module. The module fronts were printed laying on their inner face, so it could not be easily printed as part of the face. Instead this was separated into another part which would need to be bolted to the front face. Yet there is so little space between the light box and two sides of the module that it could not be bolted very securely. My solution was to move some of the material of the module box on to the light box to create a rim, and incorporate the bolts which held the module face to the box, sandwiching the light box.

> ![Rim on the light box](https://i.imgur.com/aJ5DVzg.jpg)
> 
> Showing the light box with a rim

> ![The light box sandwiched by the face and box](https://i.imgur.com/AXsluYY.jpg)
> 
> The light box sandwiched by the face and box

Sticking with the transparent plastic, the downside to the difficulty in very clear prints meant that the button cover ended up frosted. This isn't ideal but not a deal-breaker. There's certainly no off-the-shelf product that could hold the button given how large these buttons are...

> ![Button cover](https://i.imgur.com/W5ACno1.jpg)
> 
> The button cover, still able to squint and see the button inside

The hinge was very difficult to modle and also print, but I think I got quite lucky with this one. I'd started to dial in the tolerances so parts slotted together snuggly, and somehow lucked-out in that the hinge would stay in place so that buton cover won't fall on your fingers when you're holding the button.

For the button mechanism, I had originally thought of clamping it in place but decided to continue my trend of attempting difficult prints and wanted to use the threads of the button mechanism. There are a couple of threads I used: one to screw the main body of the button into the face of the module, and another screw for the button cap. I'd specifically tracked down a mechanism which had detachable button caps to make changing the button really easy between games, and although the thread seemed far too tiny to print, it actually worked very well (and my surprise was very great considering I was eye-balling the thread size with my calipers)! After a lot of trial and error to nail down the start of the thread, I could print buttons which would orient themselves correctly when screwed tightly in place!

Then came a *lot* of printing! I needed 20 buttons for a set: 4 labels in 5 colours. The buttons were printed in two parts and bolted together, which was simply done to keep the print simple and efficient. I also had to spend a lot of time tweaking the font to be able to import it into Fusion 360, and more time to get a two-colour print with my single-extruder printer. Unless you get very close, the button labels look really nice.

> ![Buttons!](https://i.imgur.com/UIkJiwQ.png)
> 
> Button bolts and screw thread

> ![Buttons!](https://i.imgur.com/9WIsGkZ.jpg)
> 
> Lots of buttons!

And after alllll of that design and printing work, this module was done!

> ![The finished button module](https://i.imgur.com/xPh4FBU.jpg)
> 
> The finished Button module

### Keypads

Another tricky one. Again, the main components to integrate were the key switches and LED bulbs, but creating switchable, oversized keycaps involved a *lot* of attempts to get right.







> ![Bomb case CAD](https://i.imgur.com/9ShPnQB.png)
> 
> The initial design of the bomb case




### Wrapping up

This all happened over the course of a few months. It took a lot of time to build, disassemble, reassemble, etc the case when I needed to make a major adjustment or addition, all while working on more module designs and programming new modules. But it was all starting to come together and I could see what the finished product might actually look like.

There was still a lot of work to be done just on the case. The outer frame was not attached to the inner case for the majority of the time as the widgets and side panels had not been concepted yet, and big questions remained over how this would best be done. So I'll save that story for a later post...

[Prev post: Building the case](devblog_12.md)
