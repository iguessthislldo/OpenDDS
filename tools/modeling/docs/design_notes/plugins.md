<!--
  This file was coverted mannually from a TiddlyWiki called plugins.html 
-->
# OpenDDS Modeling SDK Plugins

  * [ApplicationPackage](#applicationpackage)
  * [Code Generation](#code-generation)
  * [CorePackage](#corepackage)
  * [DCPSPackage](#dcpspackage)
  * [DCPSProfile](#dcpsprofile)
  * [Details](#details)
  * [DomainPackage](#domainpackage)
  * [EMF Details](#emf-details)
  * [OpenDDS package](#opendds-package)
  * [Remaining packages](#remaining-packages)
  * [EMF Issues](#emf-issues)
  * [EMF Models](#emf-models)
  * [EnumerationsPackage](#enumerationspackage)
  * [GMF Details](#gmf-details)
  * [Definitions](#definitions)
  * [Steps](#steps)
  * [Steps for GMF model changes](#steps-for-gmf-model-changes)
  * [Steps for Java code changes](#steps-for-java-code-changes)
  * [Custom policies](#custom-policies)
  * [Shared policies](#shared-policies)
  * [GMF Issues](#gmf-issues)
  * [GMF Models](#gmf-models)
  * [Issues](#issues)
  * [Plug-in TODO](#plug-in-todo)
  * [QoSPackage](#qospackage)
  * [TopicsPackage](#topicspackage)
  * [TypesPackage](#typespackage)
  * [`org.opendds.modeling.feature`](#orgopenddsmodelingfeature)
  * [`org.opendds.modeling.help`](#orgopenddsmodelinghelp)
  * [`org.opendds.modeling.model`](#orgopenddsmodelingmodel)
  * [org.eclipse.emf.ecore.generated_package](#orgeclipseemfecoregenerated_package)
  * [org.eclipse.core.resources.natures](#orgeclipsecoreresourcesnatures)
  * [org.eclipse.emf.ecore.extension_parser](#orgeclipseemfecoreextension_parser)
  * [`org.opendds.modeling.model.edit`](#orgopenddsmodelingmodeledit)
  * [`org.opendds.modeling.model.editor`](#orgopenddsmodelingmodeleditor)
  * [`org.opendds.modeling.sdk`](#orgopenddsmodelingsdk)
  * [org.eclipse.ui.editors](#orgeclipseuieditors)
  * [org.eclipse.ui.newWizards](#orgeclipseuinewwizards)
  * [`org.opendds.site`](#orgopenddssite)

The OpenDDS Modeling SDK is built from a set of Eclipse plug-in projects and
distributed as a Feature that includes the set of plug-ins required. The
plug-ins include:

| Plugin Package | Description |
| --- | --- |
| [`org.opendds.modeling.model`](#orgopenddsmodelingmodel) | Ecore metamodel and profile definition derived from the OMG UML Profile for DDS (http://www.omg.org/spec/UML4DDS/1.0/Beta1/PDF/). |
| [`org.opendds.modeling.model.edit`](#orgopenddsmodelingmodeledit) | Edit support for the `org.opendds.modeling.model` ecore model. |
| [`org.opendds.modeling.model.editor`](#orgopenddsmodelingmodeleditor) | Generated EMF editor for the `org.opendds.modeling.model` ecore model. |
| odeling.gmf | GMF graphical modeling framework for graphical model capture based on the `org.opendds.modeling.model` ecore model. |
| `org.opendds.modeling.graphics` | GEF Graphics Figure Gallery for diagrams. |
| `org.opendds.modeling.diagram.main` | Main SDK model capture diagram. This is the component diagram to capture the OpenDDS artifacts. |
| `org.opendds.modeling.diagram.policylib` | QoS Policy lib capture diagram. This captures the non-default QoS policy values. |
| `org.opendds.modeling.diagram.datalib` | Data type library capture diagram. This captures the data types and structures used by the middleware. |
| [`org.opendds.modeling.sdk`](#orgopenddsmodelingsdk) | Top level SDK plug-in including the code generation capability from the capture models. |
| [`org.opendds.modeling.feature`](#orgopenddsmodelingfeature) | Feature definition for the OpenDDS Modeling SDK. |
| [`org.opendds.modeling.help`](#orgopenddsmodelinghelp) | Help plug-in for the SDK.|
| [`org.opendds.site`](#orgopenddssite) | Plug-in distribution site. This is where Eclipse can find the plug-ins for installation. |


These eclipse projects are stored in two separate repositories. Most are held
in the [OpenDDS source repository](https://github.com/objectcomputing/OpenDDS),
while the `org.opendds.site` plug-in is held in the Object Computing, Inc. (OCI)
internal repository for the http://www.opendds.org/ website. This allows
updates to the site to be managed directly from the subversion sources. During
development the `org.opendds.site` plug-in is located in a development repository
to allow test installation and updates to be performed. The site plug-in will
be moved to the opendds.org repository as the SDK is released.

The public update site is located at:
http://www.opendds.org/modeling/eclipse/plugins. Until the initial version of
the SDK is released, this site will not be available for installation or
updates. A development site will be maintained for internal use.

The plug-in projects are being developed initially in the 'branches/RT13927'
branch. The source and associated information is located in the
'tools/modeling' directory, with the plug-ins located in the
'tools/modeling/org.opendds' directory. An internal distribution site is
available during development for testing the distribution mechanism.

## ApplicationPackage

Section 7.1.11 of the specification defines the **Application** package of the metamodel.  The ecore model for this includes the _ApplicationTarget_ classifier as well as definitions for the _LanguageType_, _PlatformType_, and _ComponentType_ enumerations used as fields of the _ApplicationTarget_ classifier.  This model has the following properties:
 - package: `org.opendds.modeling.model`
 - file: `org.opendds.modeling.model`/models/Application.ecore
 - namespace: Application
 - ns prefix: application
 - location: `http://www.opendds.org/modeling/schemas/Application/1.0`
{{imgcenter{[img[images/Application.png]]

## Code Generation

Transforming the captured model into an executable application is done using the [[`org.opendds.modeling.sdk`]] plug-in.  This plug-in provides a code generation multi-page editor and contributes actions to the SDK menus and toolbars for generating code.

Design notes for the actual code generation translations, generated code, support libraries, and usage examples are maintained in a separate [document](codegen.html).
## CorePackage

Section 7.1.2 of the specification defines the **Core** package of the metamodel.  The ecore model for this includes the _Entity_, _TypedEntity_, and _Specification_ classifiers.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/Core.ecore
* namespace: Core
* ns prefix: core
* location: `http://www.opendds.org/modeling/schemas/Core/1.0`
{{imgcenter{[img[images/Core.png]]

## DCPSPackage

Section 7.1.6 of the specification defines the **DCPS** package of the metamodel.  The ecore model for this includes the _Domain_, _DomainParticipant_, _Publisher_, _Subscriber_, _DataWriter_ and _DataReader_ classifiers corresponding to DDS Entities as well as intermediate abstract classifiers of _PublisherSubscriber_ and _DataReaderWriter_ to group properties and interfaces with.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/DCPS.ecore
* namespace: DCPS
* ns prefix: dcps
* location: `http://www.opendds.org/modeling/schemas/DCPS/1.0`
{{imgcenter{[img[images/DCPS.png]]

## DCPSProfile

Section 7.2 of the specification defines the DDS Profile using the previously defined metamodel classifiers.  Stereotypes are defined for each construct that can be added to a DDS model.  The ecore model for this includes the definitions for all of the specified stereotypes as well as some additional

## Details

For some of the SDK implementation steps there are limited or no instructions on how to reproduce the steps. For the situations the step details are captured in this section.
*[[EMF Details]]
*[[GMF Details]]

## DomainPackage

Section 7.1.3 of the specification defines the **Domain** package of the metamodel.  The ecore model for this includes the _DomainEntity_, and _QosProperty_ classifiers.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/Domain.ecore
* namespace: Domain
* ns prefix: domain
* location: `http://www.opendds.org/modeling/schemas/Domain/1.0`
{{imgcenter{[img[images/Domain.png]]

## EMF Details

 - OpenDDS Generator Model adjusts
There are some slight changes in the OpenDDS.genmodel file from what is generated by the EMF Generator Model wizard. (See the EMF book section 12.3 for definitions of these properties.) These differences are given below.

Note that if there are changes to the underlying modeling it may be easier to reconstruct the file as it has been found that in some cases the properties for new modeling elements were not the same as what the wizard would have generated from scratch.

## OpenDDS package
For the OpenDDS package that directly follows the top level element:
 - In section All change Base Package to `org.opendds.modeling.model`
 - In section All change Prefix to OpenDDS

## Remaining packages
For the remaining packages (Core, Domain, etc.):
 - In section All change Base Package to `org.opendds.modeling.model`
 - In section All change the Prefix so it reflects the case used in the package's ecore file (e.g. change Dcps to DCPS, Qos to QoS) as needed
 - In the section Editor change Generate Model Wizard to false
 - In the section Tests change Generate Example Class to false

## EMF Issues

 - GMF and Package Names

There is a defect in GMF, [Code generation problems with upper case letters in metamodel package ]( https://bugs.eclipse.org/bugs/show_bug.cgi?id=205066), that causes GMF to emit a Java import of a package instead of a class (eclipse will report a "Only a type can be imported" error). To work around this the top-level package in the `org.opendds.modeling.model` Ecore files have all lowercase characters in their name. Note that this results in packages names that differ by case from what is in the DDS Profile specification (e.g. "dcps" instead of "DCPS").

## EMF Models

The OpenDDS Modeling SDK is based on the OMG "UML Profile for Data Distribution Specification" ([ptc/08-07-02](http://www.omg.org/spec/UML4DDS/1.0/Beta1/PDF/)).  This specification contains metamodel definitions and a UML Profile.  The SDK defines the metamodel as Eclipse ecore models.  It then loads the metamodel resources into another ecore model and defines the stereotypes of the profile.  This is used to create a model with an EMF editor, which can be used to provide a tree based view and editing, that can then be mapped onto a Graphical Modeling Framework (GMF) model for graphical model capture.

The Eclipse Modeling Framework (EMF) will take the captured ecore models defining the metamodel and profile and create edit support and a tree based EMF editor for the profile.  The model can also be mapped into the GMF models for graphical capture and the EMF and GMF editors coordinated to show the different views of the same underlying model.  The EMF Eclipse plug-in packages implementing this include:

| EMF Model Packages | Description |
| --- | --- |
| `org.opendds.modeling.model` | Package containing the ecore model files defining the metamodel and profile stereotypes. |
| `org.opendds.modeling.edit` | Package generated from the ecore models containing edit support used by the editor. |
| `org.opendds.modeling.editor` | Package generated from the ecore models containing the EMF editor for the metamodel. |

The generated packages include some specific tailoring as well.  The EMF editor generation steps will not overwrite the existing modfications.

The individual metamodels are broken into separate packages by the specification.  This is mirrored by having separate ecore metamodels for each specification package.  This allows the metamodels to use the same namespaces as those in the specification.  The DLRL portion of the specification is not included in this SDK.  The metamodel packages / ecore models are:

| Package | Specification Section | Ecore model file |
| --- | --- |
| CorePackage | 7.1.2 | Core.ecore |
| DomainPackage | 7.1.3 | Domain.ecore |
| TopicsPackage | 7.1.4 | Topics.ecore |
| TypesPackage | 7.1.5 | Types.ecore |
| DCPSPackage | 7.1.6 | DCPS.ecore |
| QoSPackage | 7.1.7 | QoS.ecore |
| EnumerationsPackage | 7.1.8 | Enumerations.ecore |
| ApplicationPackage | 7.1.11 | Application.ecore |
| DCPSProfile | 7.2 | OpenDDS.ecore |

Details for settings that are different from default EMF settings can be found in [[EMF Details]].
Issues related to usage can be found in [[EMF Issues]].

## EnumerationsPackage

Section 7.1.8 of the specification defines the **Enumerations** package of the metamodel.  The ecore model for this includes definitions for enumerations used as field of QoS policies.  Inexplicably, this also includes a structure definition for the _Period_ classifier which is not an enumeration but a compound type used as a field type for various policies.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/Enumerations.ecore
* namespace: Enumerations
* ns prefix: enumerations
* location: `http://www.opendds.org/modeling/schemas/Enumerations/1.0`
{{imgcenter{[img[images/Enumerations.png]]

## GMF Details

### Making sure Java has enough PermGen memory

It was found running SDK diagram code under Ubuntu 9.10 running eclipse 3.5.1 that the Java PermGen memory hit the maximum PermGen memory allowed causing the diagram code to crash. The PermGen memory is used to hold meta data about user classes.

This condition is seen the Error log as

```
# MESSAGE Error occurred during status handling
# STACK 0
java.lang.OutOfMemoryError: PermGen space
```

In the case that this was seen the PermGen maximum size was about 88MB.

The maximum size can be set using the -XX:MaxPermSize argument. For example, to
set the maximum PermGen size to 128MB, pass `-XX:MaxPermSize=128m` to the Java
VM.

Note the _PermSize_ term is used for for referring to _PermGen_ space.

Also note that any such setting made in eclipse.ini does not apply to launching an eclipse application from within eclipse (Run As -> Eclipse Application). Instead it is necessary to add the MaxPermSize argument to the VM arguments in the Run Configuration setting.

### Sub-diagrams
GMF supports the capability to double-click on a diagram node and have it open up another diagram. GMF calls this _diagram partitioning_. Unfortunately, GMF 2.2.2 does not directly support diagram partitioning through it's views and wizards when the diagram node's domain element is not the same as the canvas mapping's domain element in the sub-diagram, which is how the SDK uses sub-diagrams. The steps given here were used to produce the sub-diagram capability of the SDK.

The starting point for these steps are the [Diagram Partitioning wiki page|http:_wiki.eclipse.org/Diagram_Partitioning]] that was extract from a [GMF newsgroup post](http:_dev.eclipse.org/newslists/news.eclipse.modeling.gmf/msg06184.html), and the discussion in section 4.5.6  of the eclipse Modeling Project book.

## Definitions

The terms and definitions used here are taken from the Diagram Partitioning wiki. Replace references to "My Library" below with the appropriate package the diagram is based on (e.g. "PolicyLib") in the discussion that follows.

|!Term|!SDK Example|!Definition|h
|Partitioning node|The package shown in the main diagram|The node that can be double-clicked on open the sub-diagram.|
|Super-diagram|Main Diagram|The diagram that contains the partitioning node.|
|Super-mapping|MainDiagram.gmfmap|The GMF mapping file for the super-diagram.|
|Sub-diagram|My Library diagram|The diagram that is opened after double-clicking on the partitioning node.|
|Sub-mapping|MyLibrary.gmfmap|The GMF mapping file for the sub-diagram.|

## Steps

### 1. Define the Main Diagram tools
File used: MainDiagram.gmftool
Create MainDiagram.gmftool and have the palette only contain those elements that can show up on the main diagram. (GMF does not restrict what shows up on the palette based on the top level nodes and links that can be created on the diagram, so we want a single tooling definition for each diagram to avoid the user picking inappropriate elements.)

### 2. Define the Main diagram mapping
File used: MainDiagram.gmfmap

Use the UML Package diagram in the project `org.opendds.modeling.uml`2tools.mirrored for the graphics definition model in MainDiagram.gmfmap and use OpenDDSModel found in OpenDDS.ecore as the Canvas mapping element.

### 3. Define My Library diagram tools
File used: MyLibrary.gmftool

 - Bring up the Tooling Definition wizard. From the context menu select New -> Other -> Graphical Modeling Framework -> Simple Tooling Definition Model.
 - Pick OpenDDS.ecore as the file containing the ecore domain model. (In the case of the DataLib, Types.ecore was specified.)
 - Pick MyLibrary as the diagram element.
 - Unselect elements that shouldn't appear in the palette in the "Domain model elements to process" dialog.
 - Note that the order of tools is based on their order in the model. You may want to edit the content and sort the tools alphabetically.

Below is a python script that help re-order the palette tools. It is first necessary to come up with file that has a tool per line that can be in any order that can be piped to the script.

```python
#! /usr/bin/python

# Purpose: Given a list of tools in standard input to be used in a GMF palette,
# generate the XML to put in the .gmftool file sorted by tool name.

import sys
from string import Template

toolTemplate = Template(
'''      <tools
          xsi:type="gmftool:CreationTool"
          title="$tool"
          description="Create new $tool">
        <smallIcon
            xsi:type="gmftool:DefaultImage"/>
        <largeIcon
            xsi:type="gmftool:DefaultImage"/>
      </tools>''')

tools = sys.stdin.readlines()

for t in sorted(tools):
    print toolTemplate.substitute(tool=t.rstrip())
```

### 4. Specify unique class name qualifier for sub-diagram GMF generator model
Files used: OpenDDS.genmodel, OpenDDS_dup_MyLibrary.genmodel

In anticipation of being able to bring up a My Library subdiagram by double-clicking on a MyLibrary node in the main diagram, a near duplicate of OpenDDS.genmodel will be created here and referred to later when the EMF generator model is requested.

What needs to be done is to change qualifer that prepends generated class names. As stated in step 6 of the Diagram Partitioning wiki, this is the "hacky" part needed because of how the dependency on EMF generator model is handled. Although this step is not mentioned in the eclipse Modeling Project book, failure to do this results the error

> Unable to open editor, unknown editor ID: `org.opendds.modeling.model.opendds.diagram.mylibrary.part.OpenDDSMyLibraryDiagramEditorID`

 - Copy OpenDDS.genmodel to OpenDDS_dup_MyLibrary.genmodel.
 - In OpenDDS_dup_MyLibrary.genmodel change the Model Name property to OpenDDSMyLibrary.

### 5. Define My Library diagram mapping
File used: MyLibrary.gmfmap

- Bring up the Mapping Definition wizard. From the context menu select New -> Other -> Graphical Modeling Framework -> Guide Mapping Model Creation.
- Pick OpenDDS.ecore as the file containing the ecore domain model.
- Pick MyLibrary as the diagram element.
- Pick MyLibrary.gmftool created from the previous step as the diagram palette.
- Pick the appropriate mirrored graphic file in `org.opendds.modeling.uml`2tools.mirrored. For the My Library this is classDiagram_classifiers.mirrored.gmfgraph.
- In the "Map domain model elements" dialog remove inappropriate links. In the case of the My Library this is all links. Verify that all the nodes used in the mapping are appropriate.

### 6. Create the My Library GMF generator model
File used: MyLibrary.gmfgen

 - From the context menu for MyLibrary.gmfmap, select "Create generator model..." and use the defaults provided by the wizard.

#### 6.1 Gen Editor Generator category changes

| Copyright Text | (c) Copyright Object Computing, Incorporated.  2005,2010.  All rights reserved. |
| Diagram File Extension | opendds_diagram_mylibrary |
| Package Name Prefix | `org.opendds.modeling.model.opendds.diagram.mylibrary` |
| Model ID | OpenDDS MyLibrary |

#### 6.2 Gen Plugin

| ID | `org.opendds.modeling.diagram.mylibrary` |
| Name | OpenDDS MyLibrary Plugin |
| Provider | Object Computing, Inc. |
| Version | (current version) |

### 7. (Optional) Check that the sub-diagram works

File used: MyLibrary.gmfgen

To verify that the sub-diagram works correctly, you can run launch the
diagram editor for the sub-diagram after creating the My Library
GMF generator model (MyLibrary.gmfgen).

Before doing this close project `org.opendds.modeling.diagram.main` if
it exists. Otherwise you may see in the error log the message

> Both `org.opendds.modeling.diagram.main` and `org.opendds.modeling.diagram` register an extension parser for `opendds_diagram`

After verifying the sub-diagram works re-open project `org.opendds.modeling.diagram.main.`

### 8. Relate the sub-diagram to the super-diagram
File used: MainDiagram.gmfmap

 - Open MainDiagram.gmfmap with the GMF Map Model editor
 - Load as a resource MyLibrary.gmfmap
 - Go to the Node Mapping for the My Library
 - Under the Misc category edit the value for Related Diagrams
 - Add the second Canvas Mapping in the list
 - In a text editor verify that the relatedDiagrams element of the My Library node points to MyLibrary.gmfmap.

### 9. Update Gen Editor View for the super-diagram GMF generator model
Files used: MainDiagram.gmfgen, MyLibrary.gmfgen

 - Update (context menu item "Create generator model..." for MainDiagram.gmfmap) the MainDiagram.gmfgen to account for changes made in the previous step.
 - Open MainDiagram.gmfgen.
 - Go to node Gen Diagram OpenDDSModelEditPart -> Gen Top Level Node MyLibraryEditPart -> Open Diagram Behavior
 - Set property Diagram Kind to OpenDDS MyLibrary.
 - Set Edit My Class Name to OpenDiagramEditPolicyMyLibrary.
 - We need the Gen Editor View ID for the sub-diagram. Open MyLibrary.gmfgen and go to Gen Editor Generator -> Gen Editor View `org.opendds.modeling.model.opendds.diagram.mylibrary.part` and copy the value for ID into the clipboard.
 - Back in MainDiagram.gmfgen, go to node Gen Diagram OpenDDSModelEditPart -> Gen Top Level Node MyLibraryEditPart -> Open Diagram Behavior OpenDiagramEditPolicy, set property Editor ID to what is in the clipboard.

### 10. Test sub-diagram usage

 - Re-generate project `org.opendds.modeling.diagram.main.`
 - Generate project `org.opendds.modeling.diagram.mylibrary.`
 - Launch `org.opendds.modeling.diagram.main` as an eclipse application.
 - Create a new OpenDDS diagram.
 - Create a MyLibrary package and double-click on the package.
 - Verify that the sub-diagram opens up allowing to to add elements to the package.
 -
 - UML Component figures with classes arbitrarily positioned

For the SDK DCPS diagram UML components for domain participants are used. Simple attempts to do this using the GMF layout XY Layout were tried without success. Elements in the component would be as small as possible and stack on top of each other. Attempts to follow the lead of the UML2Tools Component was not successful either. For figure ComponentFigure_Body used by the compartment the custom layout org.eclipse.gmf.runtime.draw2d.ui.figures.OneLineBorder is used and attempts to reproduce this also resulted in stacked elements.

As a workaround an attempt was made to stack the elements on top of each other as is done with the DNC Package node as described in section 4.6, Developing the Color Modeling Diagram, in the Eclipse Modeling Project book. However, if side-affixed node was attached to an element (to represent a port) in the component it did not render properly nor was the label for the node visible. So this approach was not feasible.

Finally, it was noticed after checking out the project for the [GMF taipan example](http://wiki.eclipse.org/index.php/GMF_Tutorial) from the CVS repository dev.eclipse.org that the Ship cargo compartment allowed cargo to be arbitrarily placed in the compartment. After investigating how this was done it found that the undocumented compartment setting listLayout in the .gmfgen file was set to false instead of the default value of true. For some reason this setting will override any layout setting used for the compartment's figure.

Therefore, if a compartment's figure is to have XY Layout, make sure in the settings for the compartment in the .gmfgen file have listLayout set to false.

 - Support for enumerations in class figures

For direct editing of Ecore attributes in figures, GMF does not support providing a list of attributes from which the user can select from (see bug entry [Support enum based labels](https://bugs.eclipse.org/bugs/show_bug.cgi?id=158116)). Instead, the user must type out exactly what the enumeration value is. This means, for example, that when editing a DestinationOrderQosPolicy the user must type in (in the correct case) either BY_RECEPTION_TIMESTAMP or BY_SOURCE_TIMESTAMP to change the kind attribute. This makes modification of QoS Policy enumerations error prone and tedious.

The source files that need modification are in project `org.opendds.modeling.diagram.policylib`'s package `org.opendds.modeling.model.opendds.diagram.policylib.edit.parts.` The file are

* DestinationOrderQosPolicyKindEditPart.java
* DsQosPolicyHistory_kindEditPart
* DurabilityQosPolicyKindEditPart.java
* HistoryQosPolicyKindEditPart.java
* LivelinessQosPolicyKindEditPart.java
* OwnershipQosPolicyKindEditPart.java
* PresentationQosPolicyAccess_scopeEditPart.java
* ReliabilityQosPolicyKindEditPart.java

To provide a list in the form of a combo box from which the user can select enumeration literals from, a set of classes has been written that modified GMF generatored code can use. This section outlines how to do that.

## Steps for GMF model changes

### 1. Graphical Definition Model

A diagram label is used for the enumeration which the GDM wizard may have already created for you. Just make sure that the Element Icon property is set to false.

### 2. Mapping Model

A Feature Label Mapping is used for the enumeration that is owned by the node associated with the enumerator's parent.

For the Visual representation category of the Feature Label Mapping properties use the following settings, replacing attribute-name with the name of enumeration attribute (for example, for the DestinationOrderQosPolicy the name for the DestinationOrderQosPolicyKind enumeration is "kind"):

|!Property|!Value|h
|Editor Method|{0}|
|Edit Method|{0}|
|View Method|attribute-name: {0}|


## Steps for Java code changes

The only Java class that needs to be modified is the EditPart that corresponds to the attribute, so the steps that follow apply only to that file. We'll call the Java interface corresponding to the Ecore enumeration attribute is `org.opendds.modeling.model.enumerations.MyEnum.`

Note that if the format of the code fragments below looks odd it is based on the format GMF applies to "@generated NOT" methods when it re-generates the code.

### 1. Add imports

Import the enumeration specific direct edit classes and the enumeration interface generated by EMF.

Note that after all the changes have been made there will be unused imports for LabelDirectEditPolicy and TextDirectEditManager but they will be included after GMF does code generation so there is no need to remove them.

```java
import com.ociweb.gmf.EnumDirectEdit.EnumDirectEditManager;
import com.ociweb.gmf.EnumDirectEdit.EnumDirectEditPolicy;
import org.opendds.modeling.model.enumerations.MyEnum;
```

### 2. Specify that the EnumDirectEditPolicy will be used

Replace LabelDirectEditPolicy with EnumDirectEditPolicy.

```java
	/**
	 * @generated NOT
	 */
	protected void createDefaultEditPolicies() {
                ...
		installEditPolicy(EditPolicy.DIRECT_EDIT_ROLE,
				new EnumDirectEditPolicy(MyEnum.class));
                ...
```

### 3. Specify that the EnumDirectEditManager will be used

```java
	/**
	 * @generated NOT
	 */
	protected DirectEditManager getManager() {
		if (manager == null) {
			setManager(new EnumDirectEditManager(this, EnumDirectEditManager
					.getCellEditorClass(), MyEnum.class));
		}
		return manager;
	}
```

### 4. Use the EnumDirectEditManager in the performDirectEdit() methods

```java
	/**
	 * @generated NOT
	 */
	protected void performDirectEdit(Point eventLocation) {
		if (getManager().getClass() == EnumDirectEditManager.class) {
			((EnumDirectEditManager) getManager()).show(eventLocation
					.getSWTPoint());
		}
	}

	/**
	 * @generated NOT
	 */
	private void performDirectEdit(char initialCharacter) {
		if (getManager() instanceof EnumDirectEditManager) {
			((EnumDirectEditManager) getManager()).show(initialCharacter);
		} else {
			performDirectEdit();
		}
	}
```

### 5. Verify adjusted methods will not be overwritten

Check that there the four occurrences of "@generated NOT" are the source file so that your changes
will not get overwritten the next time GMF re-generates the runtime code.

 - Domain Entities and QoS Policies

A requirement for DCPS domain entity modeling is that a QoS policy associated with a domain entity
can either be custom (or "owned") by the domain entity, or referenced ("shared") from a policy library.

The metamodel or profile in the DDS profile specification does not directly support  the notion of custom
verses shared policies, however the  worked example shows the usage of QoS policy library as can be
seen in section 7.3.1 of the specification.

To support either custom or shared policies in the SDK the DcpsLib Ecore element contains a collection of qosPolicy references similar to the policy collection found in a PolicyLib. DcpsLib's policy collection is not intended to be manipulated directly by the user. Instead, code generated by GMF has been customized to give the appearance that
a domain entity owns its custom policies. This is needed because GMF assumes that the Ecore objects behind
the child nodes in a parent figure's compartment are owned by the Ecore object the parent figure.

This customization of GMF generated code is the largest set of changes found in the SDK diagram code. Below the details involved in supporting custom verses shared policies is given.

## Custom policies

A custom policy has a lifecycle that is bounded by the lifecycle of its parent domain entity.

### Adding context menu items for domain entities

Custom policies are adding by the user using context menus for the domain entity. For each domain entity there
must be a concrete class that inherits from generic class `org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibCreateQosPolicyAction.` For example,
`org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibCreateQosPolicyActionDataReader` inherits from
OpenDDSDcpsLibCreateQosPolicyAction to provide a concrete action for adding shared policies to DataReaders.

In `org.opendds.modeling.diagram.dcpslib`/plugin.xml the extension point org.eclipse.ui.popupMenus includes
contribution that provide the "Add QoS Policy" context menu item and "Add custom QoS Policy"
sub-menu item for the domain entities. For example, the DataReader has the action element:

```xml
         <action
               class="`org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibCreateQosPolicyActionDataReader`"
               enablesFor="1"
               id="`org.opendds.modeling.popup.DataReaderCreatePolicyActionID`"
               label="Add &amp;custom QoS Policy"
               menubarPath="DataReaderInsert/group1">
         </action>
```

### Modify policy's CreateCommand to add to DcpsLib policies and to domain element

When creating a custom policy it must be both added to it's container (the domain element's DcpsLib) and added as a reference to
the domain element.

See for example
`org.opendds.modeling.model.opendds.diagram.dcpslib.edit.commands.EfQosPolicyCreateCommand.doExecuteWithResult`()
for an example how to do this.

## Shared policies

A shared policy has a lifecycle that can be beyond the lifecycle of a domain entity that references it.

### Going from a QosPolicy to a label to use in dialogs

To support allowing the user to select shared policies from a dialog it is necessary when presenting a policy to
that the user knows which DataLib that owns the policy since candidate policies to select from may
have the same name. The capability is provided by `org.opendds.modeling.diagram.dcpslib.part.QosPolicyLabeler.`

### Going from a QosPolicy to the name of the corresponding association on a domain entity

When working with domain entity policies, the user is presented with the name of the policies, not the name of the policy associations of the domain entity. For example, a DataWriter has an association to a WriterDataLifecycleQosPolicy (represented by a wdlQosPolicy stereotype). To update the domain entity we need to go from the policy stereotype name to the association name. This is handled by
`org.opendds.modeling.diagram.dcpslib.edit.commands.QosPolicyReferCommand`

### Adding context menu items for domain entities

Shared policies are adding by the user using context menus for the domain entity. For each domain entity there
must be a concrete class that inherits from generic class `org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibRefQosPolicyAction.` For example,
`org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibRefQosPolicyActionDataReader` inherits from
OpenDDSDcpsLibRefQosPolicyAction to provide a concrete action for adding shared policies to DataReaders.

In `org.opendds.modeling.diagram.dcpslib`/plugin.xml the extension point org.eclipse.ui.popupMenus includes
contribution that provide the "Add QoS Policy" context menu item and "Add reference to library QoS Policy"
sub-menu item for the domain entities. For example, the DataReader has the action element:

```xml
         <action
               class="org.opendds.modeling.diagram.dcpslib.part.OpenDDSDcpsLibRefQosPolicyActionDataReader"
               enablesFor="1"
               id="DataReaderRefQosPolicyAdd"
               label="Add &amp;reference to library QoS Policy"
               menubarPath="DataReaderInsert/group1">
         </action>
```


### Customize the Semantic EditPolicy's getDestroyElementComment() to destroy the **reference** instead.

When the user deletes a shared policy from a domain entities figure, behind the scenes we really want to
remove reference to the policy and not the policy itself.

To see how this is done, take a look, for example, at
`org.opendds.modeling.diagram.dcpslib.edit.policies.DeadlineQosPolicy`2ItemSemanticEditPolicy's getDestroyElementCommand()
to see how a DestroyReferenceCommand is used instead of a DestroyElementCommand.

## GMF Issues

### Diagram refresh problem

On Ubuntu 9.10, running eclipse 3.5.1 on top of GTK 2.10.0, there is a refresh problem for GMF based diagrams. When a diagram is opened, and either another editor tab is activated or another application is placed on top of the diagram, then after making the diagram visible again some of the diagram elements are partially or completely invisible. The only way to confidently make all the diagram elements visible again is to zoom and unzoom the diagram.

The symptoms of this problem seem similar to [Eclipse bug 164623](https://bugs.eclipse.org/bugs/show_bug.cgi?id=164623). This bug was closed as it was determined to be a problem related to GTK usage and not specific to GMF. An attempt was made to get around this by disabled anti-aliasing as discussed in the bugzilla contents but the problem persisted.

### Unable to use Graphic Definition Models from UML2Tools

It was hoped that the graphic definition models from [UML2Tools](http://wiki.eclipse.org/MDT-UML2Tools) could be reused in the SDK. However, when trying to reuse the Component graphics several issues were encountered which are listed below. Because of these problems it was decided to work with custom graphic models instead.

* Classes inside the component stack on top of each other with each class nearly the same width as the component. By contrast, when creating a component using UML2Tools, they can place elements anywhere inside the component with any size. In other words, the layout for a Component using UML2Tools appears to be using the GMF XY Layout. However, inspecting the graphical definition model it looks like a custom border is used for the figure that corresponds to the compartment holding the component elements. This was concluded by looking in project org.eclipse.uml2.diagram.def graphical definition model found in structures/componentDiagram_classifiers.gmfgraph. For figure ComponentFigure_Body used by the compartment the custom layout org.eclipse.gmf.runtime.draw2d.ui.figures.OneLineBorder is used.

* The code generated by GMF to make classDiagram_classifiers.gmfgraph using in a plug-in gives compilation errors for the PackageAsFrameFigure method

```java
	public WrappingLabel getPackageAsFrameFigure_name() {
		return getNameLabel();
	}
```

The error is

> Type mismatch: cannot convert from Label to WrappingLabel

* UML2Tools no longer active? A message in newsgroup eclipse.modeling.mdt.uml2 dated 07-26-2010 12:28am with subject "Re: Extend UML2 (EMF) and still use graphical editing" states that "the UML2 Tools project is no longer active" and pointed the thread originator to project [Papyrus](http://www.papyrusuml.org/) instead. (This may explain why a message posting on 07-22-2010 to newsgroup eclipse.modeling.mdt.uml2tools inquiring about a new release has not had any responses.) If GMF changes its underlying Ecore models for the graphic definition model, gmfgraph.ecore, in the future, it could mean that the UML2Tools graphics would have to be updated to work with the new core model. If such changes are non-trivial it could be a risk to future SDK development.

## GMF Models

[[GMF Details]] contains instructions not available elsewhere to reproduce the steps needed to for model diagram support.
[[GMF Issues]] contains known issues with the SDK's usage of GMF.
[[GMF TODO]] contains skipped tasks related to GMF that still need to be done.

## Issues

Issues encountered during the development of the OpenDDS Modeling SDK are captured here.
 - [[EMF Issues]]
 - [[GMF Issues]]
 - [[Deployment Issues]]
 - [[Dependency Issues]]
 - [[Plug-in Issues]]

## TODO

- `org.opendds.modeling.sdk`
The following are things to do for this plug-in:

### New Wizard
This should provide the following behaviors:

 - If there is a single selected container resource, populate the initial Container value with it;
 - If there is a single selected file resource, populate the initial Container with its parent and the initial model source file with the selected file;
 - Allow container browse for container;
 - Allow resource browse for model source file;
 - Allow container browse for target directory;
 - Allow target directory to be empty;
 - Require container to exist, be writable, and have an _'OpenDDS'_ nature;
 - Allow model source file to be empty;
 - Require source model file, if specified, to contain a model name (obtained via XPath expression);

### Actions
Implement Actions and Commands to allow the code generation steps to be invoked from different triggers

### Menus
 - #Create and manage an _'OpenDDS'_ top menu and context menu;
 - #Add the code generation actions to the menus;
 - #Add actions to create _'OpenDDS'_ projects, diagrams, and code generation specifications to the menus;

### Perspective
 - Create and manage an _'OpenDDS'_ perspective.

### Preferences
 - Create and manage an '_OpenDDS'_ preferences page.

## QoSPackage

Section 7.1.7 of the specification defines the **QoS** package of the metamodel.  The ecore model for this includes the abstract _QosPolicy_ classifier as well as a classifier for each policy in the DDS specification.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/QoS.ecore
* namespace: QoS
* ns prefix: qos
* location: `http://www.opendds.org/modeling/schemas/QoS/1.0`
{{imgcenter{[img[images/QoS.png]]

## TopicsPackage

Section 7.1.4 of the specification defines the **Topics** package of the metamodel.  The ecore model for this includes the _TopicDescription_, _Topic_, _ContentFilteredTopic_, and _MultiTopic_ classifiers.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/Topics.ecore
* namespace: Topics
* ns prefix: topics
* location: `http:_www.opendds.org/modeling/schemas/Topics/1.0`

## TypesPackage

Section 7.1.5 of the specification defines the **Types** package of the metamodel.  The ecore model for this includes many type definitions used for defining the data that can be transfered over DDS.  These types include both simple and compound data types.  This model has the following properties:
* package: `org.opendds.modeling.model`
* file: `org.opendds.modeling.model`/models/Types.ecore
* namespace: Types
* ns prefix: types
* location: `http:_www.opendds.org/modeling/schemas/Types/1.0`

## `org.opendds.modeling.feature`

This plug-in package is where the components of the OpenDDS Modeling Software Development Kit (SDK) are defined as a feature that can be installed as a unit.  It defines the information presented to the user during installation and updates, along with branding icons, web pages, and links.

The following plug-ins are included in this feature:

| package | description |
| --- | --- |
| `org.opendds.modeling.model` | Specification defined and OpenDDS extended meta-models and profile stereotypes. |
| `org.opendds.modeling.model.edit` | Ecore editor support for the metamodel and profile stereotypes. |
| `org.opendds.modeling.model.editor` | Ecore editors for the meta-models and Profile stereotypes. |
| `org.opendds.modeling.diagram.main` | GMF generated graphical editor to capture the top level packages of an OpenDDS model. |
| `org.opendds.modeling.diagram.datalib` | GMF generated graphical editor to capture the data definitions used by an OpenDDS model. |
| `org.opendds.modeling.diagram.policylib` |GMF generated graphical editor to capture the QoS policy definitions used by an OpenDDS model. |
| `org.opendds.modeling.sdk` |Code generation plug-in to convert an OpenDDS model to C++ code, DDS IDL, and MPC build files. |

This plug-in specifies that branding information can be found in the [[`org.opendds.modeling.sdk`]] plug-in.

## `org.opendds.modeling.help`

This plug-in will contain the HTML based help files for the SDK.

### Running Example

The Messenger example will be used as the running example, and embellished as needed to cover concepts not present in the original example.

### Structure

The overall structure for the help content is as shown below. Note that the content will evolve over time so some details may change, but the overall structure should remain fairly intact.

   - Top-level (intro to the OpenDDS SDK)
   	 - Getting Started
   		 - What is OpenDDS?
   		 - Advantages of using the OpenDDS SDK.
   		 - Known Limitations
   	 - Concepts
   		 - Modeling
   			 - Main Model
   			 - Policy Model
   			 - Data Model
   			 - DCPS Model
   			 - Reusable libraries
   		 - Code generation
    		 - Generated Code
    		 - Customizations
    		 - Application Integration
   	 - Tasks
   		 - Modeling
   			 - Defining reusable libraries
   			 - Creating Policies libraries
   			 - Creating Data libraries
   			 - Creating DCPS libraries
   			 - Using libraries
    	 - Code Generation
    		 - Creating a generation specification
    		 - Customizing the generated code
    		 - Generating the code
    		 - Integrating the generated code

   	 - Reference
   		 - QosPolicies (describe policies, map stereotypes to policies (e.g.  udQosPolicy to UserDataQosPolicy)
   		 - Data Types (describe data types that can be used)
   	 - Samples
   		 - Modeling
   			 - Sample Policy Library
   			 - Sample Data library
   			 - Sample DCPS library

## `org.opendds.modeling.model`

This package is where the OpenDDS Modeling SDK metamodels and profile are captured.  These [[EMF Models]] provide the stereotype elements that are used to capture a DCPS model using OpenDDS.  They include the individual specification package models as well as the overall OpenDDS profile model.

### Code Generation

This plug-in generates local model Java source code, the _'`org.opendds.modeling.model.edit`'_ editor support project, the _'`org.opendds.modeling.model.editor`'_ ecore editor project, and XML schema definitions for the ecore models.  This is done using the file: `models/OpenDDS.genmodel`
as the code generation specification file.  Properties for each Ecore model and generated output are defined within this specification.

### Extensions

This plug-in was created as an EMF project and implements several extension points from within the EMF project.  These include:

## org.eclipse.emf.ecore.generated_package

There are several extensions of of this EMF extension point implemented.  They define the several different Ecore models of the profile.  The models, along with the URI used for the extension point package, are:
| Class | Schema URI |
| --- | -- |
| `org.opendds.modeling.model.opendds.OpenDDSPackage` | `http://www.opendds.org/modeling/schemas/OpenDDS/1.0` |
| `org.opendds.modeling.model.core.Core` | `http://www.opendds.org/modeling/schemas/Core/1.0` |
| `org.opendds.modeling.model.domain.DomainPackage` | `http://www.opendds.org/modeling/schemas/Domain/1.0` |
| `org.opendds.modeling.model.qos.QoSPackage` | `http://www.opendds.org/modeling/schemas/QoS/1.0` |
| `org.opendds.modeling.model.topics.TopicsPackage` | `http://www.opendds.org/modeling/schemas/Topics/1.0` |
| `org.opendds.modeling.model.dcps.DCPSPackage` | `http://www.opendds.org/modeling/schemas/DCPS/1.0` |

Each of these package extensions defines an Ecore metamodel corresponding to a Module of the profile.  They are all included in the _OpenDDS.genmodel_ editor generation specification file.  Only the OpenDDSPackage package should be generated for use by the GMF editor extensions.

## org.eclipse.core.resources.natures

This extension point provides and explicit _'OpenDDS'_ nature for projects and files that are part of the SDK.  The class implementing the nature is: `org.opendds.modeling.model.opendds.OpenDDSProjectNature`

## org.eclipse.emf.ecore.extension_parser

This extension point is required in order to define the use of XMI Id values for model elements and the use of the values as the fragment part of _'href'_ attributes within the model.  This removes the positional notation that is used by default.  This is done in the class: `org.opendds.modeling.model.opendds.OpenDDSResourceFactory`

The files for which this is done are the _'.opendds'_ extension.

This plug-in depends on the installation of the following plug-ins:

 - `org.eclipse.core.runtime`
 - `org.eclipse.core.resources`
 - `org.eclipse.emf.ecore`

## `org.opendds.modeling.model.edit`

This plug-in is generated by the [[`org.opendds.modeling.model`]] plugin using the models/OpenDDS.genmodel generation specification file.  Only the plug-in Manifest and properties are not regenerated from scratch as changes are made to the source plug-in.

## `org.opendds.modeling.model.editor`

This plug-in is generated by the [[`org.opendds.modeling.model`]] plugin using the models/OpenDDS.genmodel generation specification file.  Only the plug-in Manifest, properties, and New wizard icon are not regenerated from scratch as changes are made to the source plug-in.

## `org.opendds.modeling.sdk`

This plug-in provides the code generation feature for the OpenDDS Modeling SDK.  Branding information for the entire SDK is also provided by this package.  This package is where contributions to the menus, actions, and toolbars are made as well.
### Extensions

This plug-in is a standard Eclipse plug-in and was created with a Multi-page editor.  It implements extension points for several other plug-ins.  These include:

## org.eclipse.ui.editors

A single multi-page editor is implemented from this extension point named _'OpenDDS Code Generator'_ with implementing class
  `org.opendds.modeling.sdk.codegen.CodeGenEditor`.

This editor is implemented with several UI forms and using a standard text editor as the final tab.  The editor tabs include:

| **Tab** | **Description** |
| --- | --- |
| Generate | This form includes the ability to specify the model source file and the target generation directory.  The source file is parsed for a model name and that name is used to name the generated output files.  Pushbuttons to allow generating single or all possible output files are on the form.  Generated files are placed in the specified target folder with the extracted model name and appropriate extension for the generated file. |
| Customize | This form is planned to include the ability to customize any transport specification information for the generated code.  The ability to specify that the transport information be included as generated API code or external configuration files is expected to be allowed. |
| `<filename>.codegen` | This is the text editor exposing the raw XML format of the code generation specification. |

## org.eclipse.ui.newWizards

A file creation wizard is implemented from this extension named _'OpenDDS Code Generator Specification'_ with implementing class `org.opendds.modeling.sdk.wizards.CodeGenNewWizard`
This wizard will create a single code generation specification file, with file extension _'.opendds'_ and open an editor with this file.  The wizard will suggest the selected container, if any, or the container of any selected single file, if any as the container for the new resource.

It is planned to implement using any single selected file as the suggested model input file for the code generation specification.

This plug-in depends on the installation of the following plug-ins:

 - org.eclipse.core.runtime
 - org.eclipse.core.resources
 - org.eclipse.core.filesystem
 - org.eclipse.ui
 - org.eclipse.ui.editors
 - org.eclipse.ui.ide
 - org.eclipse.ui.forms
 - org.eclipse.jface.text
 - org.apache.commons.jxpath
 - javax.xml

## `org.opendds.site`

This plug-in specifies the information to allow the OpenDDS Modeling SDK to be installed and updated as a unit.  It defines the Category: _'OpenDDS Modeling SDK'_ which is used by eclipse to group features for installation.  The [[`org.opendds.modeling.feature`]] is included under this category.
