#!/usr/bin/python
"""
"""

__version__ = '1.0'

import codecs
import csv
from datetime import datetime


def fixBom(inFile):
    bom = inFile.read(3)
    if bom == codecs.BOM_UTF16_LE or bom == codecs.BOM_UTF16_BE:
        # UTF16 BOM is only 2 bytes, so go back
        print 'UTF-16'
        inFile.seek(2)
    elif bom != codecs.BOM_UTF8:
        # No BOM to skip
        print 'no BOM'
        inFile.seek(0)


class GeneralInstructionRecord:
    def __init__(self, row, line=0):
        self.line = line
        self.name = row['Code'].strip()
        self.description = row['Description'].strip()
        self.flags = row['Flags'].strip().upper()
        self.flagsString = 'C' if 'C' in self.flags else '-'
        self.flagsString += 'Z' if 'Z' in self.flags else '-'
        self.flagsString += 'V' if 'V' in self.flags else '-'
        self.flagsString += 'N' if 'N' in self.flags else '-'
        self.is6502 = row['6502 Support'].strip().lower() != 'n'
        self.isNqsap = row['NQSAP Support'].strip().lower() != 'n'
        self.isComplete = row['Complete'].strip().lower() != 'n'
        self.notes = row['Notes'].strip()
        self.specifics = {}
        self.modes = []

    def __str__(self):
        progress = 'done' if self.isComplete else 'progress'
        platform = 'all' if self.is6502 and self.isNqsap else '6502' if self.is6502 else 'NQSAP' if self.isNqsap else 'none'
        return "{:3} {} {:25} {:4} {:5} {:8} {}".format(self.line, self.name, self.description, self.flagsString, platform, progress, self.notes)

class SpecificInstructionRecord:
    def __init__(self, row, line=0):
        self.line = line
        self.instance = row['Instance'].strip()
        self.mode = self.instance[:2]
        self.name = self.instance[-3:]
        self.opcode = row['Opcode'].strip().lower()
        self.description = row['Description'].strip()
        self.isAlu = row['ALU'].strip().lower() == 'y'
        self.bytes = row['Bytes'].strip()
        self.cycles = row['Cycles'].strip()

    def __str__(self):
        return "{} {} {} {} {} {} {} {}".format(self.instance, self.mode, self.name, self.opcode, self.description, self.isAlu, self.bytes, self.cycles)

    def tableRow(self):
        return '|' + '|'.join([self.instance, self.mode, self.name, self.opcode, self.description, self.isAlu, self.bytes, self.cycles]) + '|'

    @staticmethod
    def tableHeader():
        return '|' + '|'.join(['Instance', 'Mode', 'Name', 'Bytes', 'Cycles']) + '|'

    @staticmethod
    def tableAlign():
        return '|' + '|'.join([':---', ':---', ':---:', '---:', '---:']) +'|'


def writeFileHeader(f, title, link, excerpt):
    f.write('---\n')
    f.write('title: "{}"\n'.format(title))
    f.write('permalink: /docs/{}/\n'.format(link))
    f.write('excerpt: "{}"\n'.format(excerpt))
    f.write('---\n\n')

def writeFileFooter(f):
    dt = datetime.now().strftime("%d-%b-%Y %H:%M:%S")
    f.write('\n*this file was generated by nqsap-instructions.py at ' + dt + '*\n')


def detailsLink(name):
        # This is a specific instruction in the form AX_LDA.  Write the specific as the
        # printable text, but use the general instruction for the link.
    linkName = name[3:6] if len(name) == 6 else name
    return "[{}](../{}#{})".format(name, detailName, linkName.lower())

groupNames = {
    '0': 'A, Implicit, Relative, and Indirect - ALU Arithmetic',
    '1': 'A, Implicit, Relative, and Indirect - ALU Logic',
    '2': 'Immediate - ALU Arithmetic',
    '3': 'Immediate - ALU Logic',
    '4': 'Absolute - ALU Arithmetic',
    '5': 'Absolute - ALU Logic',
    '6': 'Absolute+X - ALU Arithmetic',
    '7': 'Absolute+X - ALU Logic',
    '8': 'Absolute+Y - ALU Arithmetic',
    '9': 'Absolute+Y - ALU Logic',
    'a': 'Indexed Indirect (X) - ALU Arithmetic',
    'b': 'Indexed Indirect (X) - ALU Logic',
    'c': 'Indirect Indexed (Y) - ALU Arithmetic',
    'd': 'Indirect+Y - ALU Logic',
    'e': 'unused',
    'f': 'unused'
}

addressModes = {
    'IP': 'Implicit',
    'AA': 'Accumulator',
    'IM': 'Immediate',
    'RE': 'Relative',
    'AB': 'Absolute',
    'AX': 'Absolute+X',
    'AY': 'Absolute+Y',
    'IN': 'Indirect',
    'IX': 'Indexed Indirect (X)',
    'IY': 'Indirect Indexed (Y)'
}

addressOrder = [ 'IP', 'AA', 'IM', 'RE', 'AB', 'AX', 'AY', 'IN', 'IX', 'IY']

opcodeGroups = [ 'P/A/R/N', 'Immediate', 'Absolute', 'Absolute+X', 'Absolute+Y', 'Indexed Indirect (X)', 'Indirect Indexed (Y)', 'NONE' ]

aluOperations = {
    '00': 'A plus 1',
    '06': 'A minus B',
    '09': 'A plus B',
    '0c': 'A plus A',
    '0f': 'A minus 1',
    '10': 'not A',
    '16': 'A xor B',
    '1b': 'A and B',
    '1e': 'A or B'
}

# Notes for unsupported instructions
supportTexts = {
    'interrupts': "No support for interrupts",
    'decimal': "No support for decimal mode",
    'hardware': "Requires hardware redesign",
    'status': "Flags register does not have access to the bus"
}

# Notes for incomplete or instructions with differences
differenceTexts = {
    'flags': "Requires V and N flags and ability to update, set, and clear individual flags. Redesign in progress to replace flags register with D flip-flops",
    'alu': "Need to share ALU opcode with the SBC operation.  Redesign in progress to override IR and force ALU into subtract mode",
    'vn flags': "Does not set V and N flags",
    'c flag': "Does not set C flag.  Will be fixed in flags redesign",
    'shift': "Requires new A register hardware",
    'zn': "Zero and Negative flags not yet set for non-ALU instructions"
}

class NotesBuilder:
    def __init__(self, texts):
        self.texts = texts
        self.notesOrder = []

    def activate(self, key):
        if key not in self.texts:
            print "FAILED to add key to notes:", key
        else:
            if key not in self.notesOrder:
                self.notesOrder.append(key)

    # Assumes key is in the notesOrder list because all keys should have called activate
    # when they were read by the file
    def getNumber(self, key):
        return self.notesOrder.index(key) + 1

    def getSubscript(self, key):
        return "<sub>{}</sub>".format(self.getNumber(key))

    def writeNotes(self, f):
        f.write("**Notes:**\n")
        for key in self.notesOrder:
            f.write('1. {}\n'.format(self.texts[key]))


def makeEnums(filename):
    print "writing", filename
    with open(filename, 'w') as f:
        f.write("// Instruction opcodes.  Those marked with an asterisk use the ALU and thus must have\n")
        f.write("// specific opcodes that match the bits that are hardwired from the IR to the ALU control.\n")
        f.write('enum {')
        lastGroup =''
        for opcode in sorted(opcodes):
            si = opcodes[opcode]
            group = opcode[2:3]
            if group != lastGroup:
                lastGroup = group
                f.write("\n    // {}0 - {}f   {}\n".format(group, group, groupNames[group]))
            if si.isAlu:
                comment = '* ' + si.description
            else:
                comment = si.description
            f.write("    {} = {},  // {}\n".format(si.instance, opcode, comment))
        f.write('};\n')

def writeInstructionTable(f, iList, notes, title):
    f.write('## ' + title + '\n\n')
    f.write('|' + '|'.join(['Name', 'Description', 'Flags', 'Address Modes']) + '|\n')
    f.write('|' + '|'.join([':---', ':---', ':---:', ':---']) + '|\n')
    for gi in iList:
        sub = notes.getSubscript(gi.notes) if notes and gi.notes else ""
        f.write('|' + '|'.join([detailsLink(gi.name)+sub, gi.description, gi.flagsString, ','.join(gi.modes)]) + '|\n')
    f.write('\n')
    if notes:
        notes.writeNotes(f)

summaryHeader = """## 6502 Compatibility

The NQSAP has a 6502-inspired architecture and instruction set.  The instructions and
registers are similar, but the opcodes of the NQSAP do not map to the same values as
a 6502.  This means that the NQSAP and 6502 are somewhat compatible at the assembly
language source level, but the object code they use is completely different.

The major difference in the two implementations is that the NQSAP is an 8-bit only machine
with no 16-bit addressing modes.  This means that the absolute addressing modes and the
zero-page addressing modes are the same because all memory is in page zero.  For
simplicity of the documentation, the instructions are listed as using absolute,
absolute+X, and absolute+Y modes instead of the zero-page modes.

Two other features of the 6502 are also not implemented: decimal mode and interrupts.
This removes a few instructions from the complete set.

One interesting difference between the two implementations is the branch instructions.
On the 6502, these use fewer cycles than an unconditional jump instruction because they
only need to specify a single byte offset instead of a two byte absolute or relative
address.  On the NQSAP, the branch instructions are expensive because they need to save
and restore one of the index registers in order to calculate relative addresses.  A set
of conditional jump instructions was added that mimics all of the conditional branches
but uses absolute addressing instead of relative addressing.  These jumps use only four
cycles instead of the eight needed for a conditional branch.

## Implementation Progress

Most of the instructions and all of the addressing modes listed here are already
implemented.  The area that needs the most work is the flags.  The current design only has
the Carry and Zero flags.  A major redesign is in progress that will add the Negative and
Overflow flags and will expand the current flags capabilities to allow setting, clearing,
and updating of individual flags rather than updating the entire flags register at once.
The new design will also add new sources to the flag inputs so that, for example, the C
flags can be updated by the shift/rotate instructions.

A second redesign is planned for the A register to enable all of the shift and rotate
functions of the 6502.  Currently, only ASL is supported because it can be done using the
74LS181 ALU chip.

The compare instructions are not implemented yet because they need the ALU to be in
subtract mode.  The ALU operation select bits are hard-wired to the Instruction Register,
so there are a limited number of opcodes that are available for each ALU operation.  The
SBC instructions are using the subtract opcodes, so there is no room to implement the
compate instructions.  A change will be made to allow the ALU select bits to be
overridded to allow the compare instructions.  This is a fairly simple change, but may
require shifting a few components to free up breadboard space.

Some of the single operand memory instructions, like INC, DEC, and ASL are not available
for the indexed addressing modes because they require too many instruction cycles.  These
instructions need to save and restore the A register and that can't be done in the eight
cycles available.  A register/flags redesign could fix this.  Another possibility is to
extend the maximum microinstruction cycles from eight to sixteen.
"""

def makeInstructionSummaries(filename):
    print "writing", filename
    iBoth = []
    i6502 = []
    iNqsap = []
    for name in sorted(instructions):
        gi = instructions[name]
        if gi.is6502 and gi.isNqsap:
            iBoth.append(gi)
            if gi.notes:
                differenceNotes.activate(gi.notes)
        elif gi.is6502:
            i6502.append(gi)
            if gi.notes:
                supportNotes.activate(gi.notes)
        elif gi.isNqsap:
            iNqsap.append(gi)

    with open(filename, 'w') as f:
        writeFileHeader(f, 'NQSAP and 6502 Instructions', 'in-summary','Instruction set summary for the NQSAP Computer')
        f.write(summaryHeader)
        writeInstructionTable(f, iBoth, differenceNotes, 'Instructions Common to 6502 and NQSAP')
        writeInstructionTable(f, i6502, supportNotes, '6502 Instructions Not Implemented in NQSAP')
        writeInstructionTable(f, iNqsap, None, 'NQSAP Extensions')
        writeFileFooter(f)

def makeInstructionDetails(filename):
    print "writing", filename
    with open(filename, 'w') as f:
        writeFileHeader(f, 'NQSAP Instructions', 'in-details','Instruction set for the NQSAP Computer')

        # Write a table of links to the instructions
        n = 0
        cols = 8
        f.write('|' + '           |' * cols + '\n')
        f.write('|' + ':---:      |' * cols)
        for name in sorted(instructions):
            gi = instructions[name]
            if not gi.isNqsap:
                continue
            if n % cols == 0:
                f.write('\n|')
            f.write("[{}](#{})|".format(name, name.lower()))
            n = n + 1
        f.write('\n\n')

        # Write a detailed description of each instruction
        for name in sorted(instructions):
            gi = instructions[name]
            if not gi.isNqsap:
                continue
            f.write('## ' + gi.name + '\n\n')
            f.write(gi.description + '\n\n')
            f.write('**Flags:** ' + gi.flagsString + '\n\n')
            f.write('|Mode|Opcode|Bytes|Cycles|\n')
            f.write(':--- |:---: |:---:|:---: |\n')
            for mode in addressOrder:
                si = gi.specifics.get(mode)
                if si:
                    f.write("|{} - {}|{}|{}|{}|\n".format(mode, addressModes[mode], si.opcode, si.bytes, si.cycles))
            f.write('\n')

        writeFileFooter(f)


def hex2(i):
    return '{:02x}'.format(int(i))


def makeInstructionsByOpcode(filename):
    print "writing", filename
    hex = '0123456789abcdef'
    with open(filename, 'w') as f:
        writeFileHeader(f, 'NQSAP Instructions by Opcode', 'in-by-opcode','NQSAP Computer Instruction set by opcode')
        f.write('## NQSAP Instructions by Opcode\n\n')
        f.write('|      |')
        for col in hex:
            f.write('  x' + col + '  |')
        f.write('\n|:---: |')
        for col in hex:
            f.write(':---: |')
        for row in hex:
            f.write('\n|**' + str(row) + 'x**|')
            for col in hex:
                gi = opcodes.get('0x'+row+col)
                if gi:
                    f.write(detailsLink(gi.instance) + '|')
                else:
                    f.write('      |')
        f.write('\n\n')
        writeFileFooter(f)


def makeInstructionsByModeGroup(filename):
    print "writing", filename
    hex = '0123456789abcdef'
    with open(filename, 'w') as f:
        writeFileHeader(f, 'NQSAP Instructions by Adddress Mode Group', 'in-by-mode-group','NQSAP Computer Instructions by Address Mode Group')
        f.write('|      |')
        for col in range(0, 8):
            f.write('{:1}<br />{:02x},{:02x}  |'.format(opcodeGroups[col], col * 0x20, col * 0x20 + 0x10))
        f.write('ALU Operation|')
        f.write('\n|:---: |')
        for col in range(0, 8):
            f.write(':---: |')
        f.write(':---         |')
        for row in range(0, 0x20):
            f.write('\n|**{0:02x}**|'.format(row))
            for c in range(0, 8):
                col = c * 0x20
                opcode = hex2(row + col)
                gi = opcodes.get('0x' + opcode)
                if gi:
                    f.write(detailsLink(gi.instance) + '|')
                else:
                    f.write('      |')
            f.write('{:13}|'.format(aluOperations.get(hex2(row), "")))

        f.write('\n\n')
        writeFileFooter(f)


# -----------------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------
instructions = {}
opcodes = {}
supportNotes = NotesBuilder(supportTexts)
differenceNotes = NotesBuilder(differenceTexts)

generalFile = 'in-general.csv'
specificFile = 'in-specific.csv'
detailName = 'in-details'

with open(generalFile, 'rb') as inFile:
    fixBom(inFile)
    reader = csv.DictReader(inFile)
    rows = 1
    for row in reader:
        rows += 1
        gi = GeneralInstructionRecord(row, rows)
        instructions[gi.name] = gi

#
wip = 0
with open(specificFile, 'rb') as inFile:
    fixBom(inFile)
    reader = csv.DictReader(inFile)
    rows = 1
    for row in reader:
        rows += 1
        si = SpecificInstructionRecord(row, rows)
        opcodes[si.opcode] = si
        #print insta
        if si.name in instructions:
            instructions[si.name].specifics[si.mode] = si
            instructions[si.name].modes.append(si.mode)
        else:
            print "No general instruction for specific", si
        if si.cycles == 'x':
            wip += 1

for name in sorted(instructions):
    gi = instructions[name]
    if not gi.specifics and gi.isNqsap:
        print "Supported instruction with no specific instructions", gi
    elif gi.specifics and not gi.isNqsap:
        print "Unsupported instruction with specific instructions", name
    # Put the instructions modes in order
    orderedModes = []
    for m in addressOrder:
        if m in gi.modes:
            orderedModes.append(m)
    gi.modes = orderedModes

makeEnums('in-enums.cpp')
makeInstructionSummaries('../_docs/in-10-summary.md')
makeInstructionDetails('../_docs/in-20-details.md')
makeInstructionsByOpcode('../_docs/in-30-by-opcode.md')
makeInstructionsByModeGroup('../_docs/in-40-by-mode-group.md')
print "opcodes={}: implemented={}, wip={}".format(len(opcodes), len(opcodes) - wip, wip)