from attributes import ASTypeAttr
from relationship import Relationship

if Relationship.SELF < Relationship.NON:
    print("Ok")

selfattr = ASTypeAttr(Relationship.SELF)
cattr = ASTypeAttr(Relationship.C)
rattr = ASTypeAttr(Relationship.R)
pattr = ASTypeAttr(Relationship.P)
nonattr = ASTypeAttr(Relationship.NON)

if selfattr < cattr < rattr < pattr < nonattr:
    if nonattr > pattr > rattr > cattr > selfattr:
        print("OK")
