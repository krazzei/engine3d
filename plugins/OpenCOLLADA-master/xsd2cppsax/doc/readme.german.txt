**********************
xsd2cppsax Anleitung
**********************

1. Aufruf des Generators
************************
xsd2cppsax ist ein Code Generator, der aus einem XSD einen C++ SAX Parser generiert. Um die
Code Generierung zu starten kann folgende Kommandozeile verwendet werden:

java -cp xsd2cppsax.jar;xercesImpl.jar de.netallied.xsd2cppsax.Main -c < Pfad zur Config Datei >

Es wird Java mindestens in Version 5 ben�tigt.

Da der generierte Code Regul�re Ausdr�cke des XSDs mit vorkompilierten pcre Ausdr�cken
validiert, muss sich pcre_compiler.exe im Working Directory befinden. 

Neben -c stehen noch zwei optionale Kommandozeilen Parameter zur Verf�gung. Diese �berschreiben
Optionen aus der Config Datei:
-i <input XSD>
-r <root element name>
Mittels dieser optionalen Parameter kann eine Config Datei mit mehreren XSDs verwendet werden.
W�hrend des generierens wird auf optionale Attribute ohne Default-Wert hingewiesen. Bei sp�terer
integration des generierten parsers in eine Anwendung muss beachtet werden, dass diese Attribute
einen undefinierten Wert haben k�nnen.



2. �ber den generierten Code
****************************
Grunds�tzlich werden zwei Klassen generiert: PublicParser und PrivateParser.
Der PrivateParser wird intern Verwendet. Er dient dazu die Text Daten des Eingabe 
Dokuments in bin�re Daten umzuwandeln (z.B. float oder URI). Au�erdem ist er in
der Lage, das Eingabe Dokument zu validieren. Die Validierung ist zur Compile-Zeit
und zur Laufzeit abschaltbar. Nachdem der PrivateParser die Text Daten geparst hat
�bergibt er sie an die Methoden des PublicParsers.

Der PublicParser ist dazu gedacht, von ihm abzuleiten. F�r jedes Element des XSDs
stellt er zwei oder drei Methoden zur Verf�gung. Die beiden die immer Verf�gbar sind,
sind eine "begin" und eine "end" Methode f�r jedes Element. Die dritte Methode beginnt
mit "data". Durch sie werden die geparsten XML Text Daten an den Implementierer 
�bergeben. Da nicht jedes Element Text Daten haben kann, ist diese Methode auch nicht
f�r jedes Element verf�gbar. Die "begin", "end" und "data" Methoden folgen dem SAX
Prinzip. Die Attribute eines Elements werden der "begin" Methode mit �bergeben. F�r
die Attribute werden C++ structs generiert. Falls erforderlich enthalten diese structs
Bit-Felder um abzupr�fen ob ein Attribut gesetzt ist oder nicht.

F�r den XSD Typ "anyURI" wird eine C++ URI Klasse verwendet. Diese stammt aus dem BaseUtils
Paket des OpenCOLLADA Projekts.

F�r XSD enums und unions werden auch C++ enums und unions generiert. Diese werden in
den Attribut structs und bei den "data" Methoden verwendet.

Eventuell auftretende Validierungs-Fehler werden an einen ErrorHandler �bergeben. Dieser
sollte vom Anwendungs-Entwickler implementiert werden. Er kann entscheiden ob bei einem
Fehler abgebrochen wird oder nicht. Es wird eine Beispiel Implementierung mit geliefert,
welche alle Fehler �ber die Standart-Ausgabe ausgibt und nie abbricht.

Dieser CoutErrorHandler befindet sich im Paket "GeneratedSaxParser" des OpenCOLLADA Projekts.
Dort befinden sich noch weitere Klassen die vom generierten Code verwendet werden. Dieses
Prjekt bietet die M�glichkeit zwei verschiedene XML Biblitheken als Basis f�r den
generierten Parser zu verwenden. Dies sind libxml und expat. Mittels Pr�pozessor
Flag kann zwischen ihnen gew�hlt werden:
- GENERATEDSAXPARSER_XMLPARSER_LIBXML
- GENERATEDSAXPARSER_XMLPARSER_EXPAT
Ein weiteres Pr�pozessor flag dient dazu, die Validierung zur Compile-Zeit einzuschalten:
- GENERATEDSAXPARSER_VALIDATION

Optional k�nnen zwei Implementierungen des PublicParsers generiert werden. Die eine,
ExampleParser, tut nichts. Sie dient als Beispiel wie ein eigener Parser implementiert
werden kann. Die andere, fprintf parser, schreibt die geparste Datei wieder in eine
andere Datei (mittles der C funktion fprinf). Sie kann f�r Performance Messungen oder 
auch als Implementierungs Vorlage dienen.

Experimentell ist auch eine dritte PublicParser Implementierung verf�gbar: CoherencyTestParser.
Er dient der �berpr�fung von COLLADA Dokumenten, ist also spezifisch f�r ein XSD. Da
er experimentell ist und kaum features bietet, wird von einer Generierung abgeraten.

Ein Gro�teil des generierten Codes wird durch Code Templates definiert. Diese Code 
Templates befinden sich in einer Datei welche von der Config Datei referenziert 
wird. Da �nderungen hieran sehr leicht zu unkompilierbarem Code f�hren k�nnen, wird 
empfohlen, die mitgelieferte Code Templates Datei unver�ndert zu verwenden.

Um eine hohe Performance zu erreichen wird innerhalb des PrivateParsers ein spezielles 
Memory Management verwendet. Wie anfangs beschrieben, parst der PrivateParser die
Text Daten des Dokuments. Um die bin�ren Daten ablegen zu k�nnen ist Speicher erforderlich.
Da die C/C++ default Speicher Verwaltung mit einer Vielzahl an spezial F�llen zurecht
kommen muss, und evtl. das Betriebssystem sogar in den Kernel-Mode wechseln muss, kann
diese sehr langsam sein. Das Memory Management des PrivateParsers ist in der C++ Klasse
GeneratedSaxParser::StackMemoryManager gekapselt. Dieser Manager alloziert zu beginn
eine bestimmte Menge Speicher (per default 1 MB). Bei Bedarf wird in diesem Speicher
ein Objekt angelegt. Die gr��e des Objekts wird am seinem Ende mit abgelegt. Diese
Gr��enangabe dient sp�ter dem korrekten freigeben des Objekts. Da der Manager nach dem
Stack Prinzip arbeitet, werden neuen Objekte immer am Ende des belegten Speichers angelegt
und es kann immer nur das letzte Objekt gel�scht werden. Das L�schen ist enorm schnell, 
da nur ein paar interne Status Variablen des Managers ge�ndert werden m�ssen. Da w�rend
des Parsens nicht immer bekannt ist, wieviel Speicher ben�tigt wird, bietet der Manager 
die M�glichkeit, dass letzte Objekt auf dem Stack zu vergr��ern. Der Speicher des Managers
wird, anders als bei C++ new, nicht initialisiert, weshalb er sich nicht f�r C++-Objekte
eignet (aber f�r pointer auf solche).

Ein weiteres Detail um die Performance zu steigern liegt im parsen von Gleitkomma Zahlen.
Anstatt C Funktionen wie atof() oder scanf() zu verwenden, verf�gt der generierte Parser
�ber eine eigene Implementierung (GeneratedSaxParser::Utils::toFloatingPoint).

W�hrend eines SAX-Parsing-Vorgangs m�ssen �blicherweise viele Strings verglichen werden
(die Element Namen) um die richtigen Funktionen aufzurufen. Um dies zu vermeiden setzt
der generierte Parser auf String Hashes. Damit wird die Performance nocheinmal gesteigert.



3. Konfigurations M�glichkeiten
*******************************
In der angesprochenen Config Datei lassen sich eine Vielzahl von Optionen festlegen.
Es wird empfohlen die mitgelieferte Beispiel Datei als Vorlage zu nehmen.
Hier Eine Auswahl der Optionen:
- Ausgabe Pfade f�r die generierten Dateien. Die Verzeichnisse m�ssen bereits existieren.
    outputHeaderFileNamePublic
    outputHeaderFileNamePrivate
    outputSourceFileNamePrivate
    outputExampleHeaderFileName
    outputExampleSourceFileName
    outputFPrintfHeaderFileName
    outputFPrintfSourceFileName
- Eingabe XSD
    inputFile
- Das Root Element des Eingabe XSDs
    rootElementName
- Klassennamen und Namespace des generierten Parsers
    namespace
    classNamePrivate
    classNamePublic
- Dateien die im generierten Code includiert werden
    includePrecompiledHeader
    includeFilesForEnumsHeader
    includeFilesForEnumsSource 
    includeFilesForImpl
    includeFilesForPrivateHeader
- Ein Header (z.B. mit Lizenz/Copyright informationen) f�r den generierten Code
    outFileHeader
- Ob XSD float und double in C++ als float oder double verwendet werden sollen
  Damit kann der Anwender selbst zwischen Geschwindigkeit und Genauigkeit w�hlen
    treatXsFloatAsCppFloat
    treatXsDoubleAsCppDouble
- Elemente die unabh�ngig vom Rest eines Dokuments geparst werden sollen
  (Bei der OpenCOLLADA Bibliothek wird das f�r die "Parser-Flags" verwendet)
    specialFunctionMapsStartElementNamesAllLevels
    specialFunctionMapsStartElementNamesOneLevel
- XSD Element Namen welche im Zusammenhang mit Complex Type Validation umbenannt werden m�ssen,
  da sie in C++ nicht erlaubt sind
    cppStructMemberNameMapping
- Generierte C++ Typnamen welche umbenannt werden sollen
  (z.B. f�r Anonyme Enums des XSDs)
    userTypeNameMapping
- XML Namespaces welche abgek�rzt werden sollen (um die Lesbarkeit zu erh�hen)
    xsNamespaceMapping
- Ob eine Beispiel Parser Implementierung generiert werden soll
    generateExampleParser
- Ob der fprintf Parser generiert werden soll
  (dieser schreibt die geparste Datei sofort wieder in eine Datei)
    generateFprintfParser
- Klassennamen und Namespace von Beispiel- und fprintf-Parser
    exampleClassName
    exampleNamespace
    fPrintfParserClassName
    fPrintfParserNamespace
- Es stehen noch weitere Optionen zur Verf�gung, die z.B. Typen und Namen 
  von Variablen im generierten Code �ndern oder zu generierten Typ-Namen 
  oder Methoden suffixe/prefixe hinzuf�gen.
  �nderungen hieran k�nnen dazu f�hren, dass der generierte Code nicht mehr kompilierbar ist.
    convenienceDataMethodLengthParameterName
    simpleValidationFunctionLengthParameterType
    cppEnumTypePrefix
    attributeStructSuffix
    ...
