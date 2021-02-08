#include "./test_group.hpp"

namespace c4 {
namespace yml {

TEST(github113, verification)
{
    // https://github.com/biojppm/rapidyaml/issues/113
    // without terminating newline:
    auto tree = parse(R"(class: Slicer
id: slicer
name: Slicer
summary: Slices a part into layers.
description: >
     A stage that slices a part based on 'flat' surfaces
     into layers.
     \<br\>
     This stage can be used to feed a surface joint
     that is registered for a perfect fit. It uses
     the previous stage profile to determine the
     layers.
     \<br\>
     Think of this stage as a step in building your own custom
     composite material.)");

    const std::string expected = "A stage that slices a part based on 'flat' surfaces"
     " into layers."
     " \\<br\\>"
     " This stage can be used to feed a surface joint"
     " that is registered for a perfect fit. It uses"
     " the previous stage profile to determine the"
     " layers."
     " \\<br\\>"
     " Think of this stage as a step in building your own custom"
     " composite material.";

    EXPECT_EQ(tree["description"].val(), expected);

    // with terminating newline:
    tree = parse(R"(class: Slicer
id: slicer
name: Slicer
summary: Slices a part into layers.
description: >
     A stage that slices a part based on 'flat' surfaces
     into layers.
     \<br\>
     This stage can be used to feed a surface joint
     that is registered for a perfect fit. It uses
     the previous stage profile to determine the
     layers.
     \<br\>
     Think of this stage as a step in building your own custom
     composite material.
)");
    EXPECT_EQ(tree["description"].val(), expected + "\n");
}


#define BLOCK_FOLDED_CASES \
    "block folded as seq val, implicit indentation 2", \
    "block folded as map val, implicit indentation 2",\
    "block folded as map val, implicit indentation 2, chomp=keep",\
    "block folded as map val, implicit indentation 2, chomp=strip",\
    "block folded as map val, implicit indentation 3",\
    "block folded as map val, implicit indentation 4",\
    "block folded as map val, implicit indentation 9",\
    "block folded as map val, explicit indentation 2",\
    "block folded as map val, explicit indentation 2, chomp=keep",\
    "block folded as map val, explicit indentation 2, chomp=strip",\
    "block folded as map val, explicit indentation 3",\
    "block folded as map val, explicit indentation 4",\
    "block folded as map val, explicit indentation 9",\
    "block folded, issue 113, pt1",\
    "block folded, issue 113, pt2",\
    "block folded, issue 113, pt3"


CASE_GROUP(BLOCK_FOLDED)
{
    APPEND_CASES(

C("block folded as seq val, implicit indentation 2",
R"(
- >
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
- another val
)",
  L{
    N("Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another val")
  }
),

C("block folded as map val, implicit indentation 2",
R"(
example: >
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, implicit indentation 2, chomp=keep",
R"(
example: >+
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n\n\n"),
    N("another", "val")
  }
),

C("block folded as map val, implicit indentation 2, chomp=strip",
R"(
example: >-
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end."),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 2",
R"(
example: >2
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 2, chomp=keep",
R"(
example: >+2
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n\n\n"),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 2, chomp=strip",
R"(
example: >-2
  Several lines of text,
  with some "quotes" of various 'types',
  and also a blank line:
  
  plus another line at the end.
  
  
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end."),
    N("another", "val")
  }
),

C("block folded as map val, implicit indentation 3",
R"(
example: >
   Several lines of text,
   with some "quotes" of various 'types',
   and also a blank line:
   
   plus another line at the end.
   
   
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 3",
R"(
example: >3
   Several lines of text,
   with some "quotes" of various 'types',
   and also a blank line:
   
   plus another line at the end.
   
   
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, implicit indentation 4",
R"(
example: >
    Several lines of text,
    with some "quotes" of various 'types',
    and also a blank line:
    
    plus another line at the end.
    
    
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 4",
R"(
example: >4
    Several lines of text,
    with some "quotes" of various 'types',
    and also a blank line:
    
    plus another line at the end.
    
    
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, implicit indentation 9",
R"(
example: >
         Several lines of text,
         with some "quotes" of various 'types',
         and also a blank line:
         
         plus another line at the end.
         
         
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded as map val, explicit indentation 9",
R"(
example: >9
         Several lines of text,
         with some "quotes" of various 'types',
         and also a blank line:
         
         plus another line at the end.
         
         
another: val
)",
  L{
    N("example", "Several lines of text, with some \"quotes\" of various 'types', and also a blank line:\nplus another line at the end.\n"),
    N("another", "val")
  }
),

C("block folded, issue 113, pt1",
R"(class: Slicer
id: slicer
name: Slicer
summary: Slices a part into layers.
description: >
     A stage that slices a part based on 'flat' surfaces
     into layers.
     This stage can be used to feed a surface joint
     that is registered for a perfect fit. It uses
     the previous stage profile to determine the
     layers.
     Think of this stage as a step in building your own custom
     composite material.)",
  L{
    N("class", "Slicer"),
    N("id", "slicer"),
    N("name", "Slicer"),
    N("summary", "Slices a part into layers."),
    N("description", "A stage that slices a part based on 'flat' surfaces"
     " into layers."
     " This stage can be used to feed a surface joint"
     " that is registered for a perfect fit. It uses"
     " the previous stage profile to determine the"
     " layers."
     " Think of this stage as a step in building your own custom"
     " composite material."),
  }
),

C("block folded, issue 113, pt2",
R"(class: Slicer
id: slicer
name: Slicer
summary: Slices a part into layers.
description: >
     A stage that slices a part based on 'flat' surfaces
     into layers.
     This stage can be used to feed a surface joint
     that is registered for a perfect fit. It uses
     the previous stage profile to determine the
     layers.
     Think of this stage as a step in building your own custom
     composite material.
)",
  L{
    N("class", "Slicer"),
    N("id", "slicer"),
    N("name", "Slicer"),
    N("summary", "Slices a part into layers."),
    N("description", "A stage that slices a part based on 'flat' surfaces"
     " into layers."
     " This stage can be used to feed a surface joint"
     " that is registered for a perfect fit. It uses"
     " the previous stage profile to determine the"
     " layers."
     " Think of this stage as a step in building your own custom"
     " composite material.\n"),
  }
),


C("block folded, issue 113, pt3",
R"(class: Slicer
id: slicer
name: Slicer
summary: Slices a part into layers.
description: >
     A stage that slices a part based on 'flat' surfaces
     into layers.
     \<br\>
     This stage can be used to feed a surface joint
     that is registered for a perfect fit. It uses
     the previous stage profile to determine the
     layers.
     \<br\>
     Think of this stage as a step in building your own custom
     composite material.)",
  L{
    N("class", "Slicer"),
    N("id", "slicer"),
    N("name", "Slicer"),
    N("summary", "Slices a part into layers."),
    N("description", "A stage that slices a part based on 'flat' surfaces"
     " into layers."
     " \\<br\\>"
     " This stage can be used to feed a surface joint"
     " that is registered for a perfect fit. It uses"
     " the previous stage profile to determine the"
     " layers."
     " \\<br\\>"
     " Think of this stage as a step in building your own custom"
     " composite material."),
  }
),
)
}

INSTANTIATE_GROUP(BLOCK_FOLDED)

} // namespace yml
} // namespace c4
